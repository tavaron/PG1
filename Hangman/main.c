//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		24.11.2011 v0.1
//      geaendert:	24.11.2011
//      
//      Beschreibung: !!!
//      
//      Eingabe: !!!
//      
//      Ausgabe: !!!
//      
//      ------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <time.h>

#define MAXWORTE 100

// Grafische Funktionen
void hangman_zeichnen(int leben, int y, int x);
void startbild();

// Spielrelevante Funktionen
int neues_spiel();
int spielen(char c, char* s, char* o);
int spielstand(char* s);

// Optionsmenue & Dateioperationen
void optionen();
int lesen();
int speichern();

// Wortoperationen
void wort_eingeben();
void wortliste();
void wort_loeschen();

// String-Deklarationen
int toupper();
int isalpha();
int isdigit();

// Globale Variablen
int woerter = 0,
	punkte = 0;
char worte[MAXWORTE][20];


int main(int argc, char** argv)
{
	char c=0;
	
	// Curses-Fenster oeffnen
	initscr();
	
	// Cursor unsichtbar machen
	curs_set(0);
	
	// stdin nicht automatisch ausgeben
	noecho();
	
	// endwin() bei Exit-Handler anmelden
	// endwin() schliesst das Curses-Fenster
	atexit((void*)endwin);
	
	// Fensterkontrolle
	int y, x;
	getmaxyx(stdscr, y, x);
	if(y<20||x<60) {
		mvprintw(0, 0, "Terminal zu klein!");
		mvprintw(1, 0, "60x20 erforderlich!");
		mvprintw(2, 0, "Beende Programm...");
		return(1);
	}
	
	// Starbildschirm
	startbild();
	
	// Schleife fuer Hauptmenue
	do
	{
		// Eingabeverarbeitung
		c = toupper(c);
		if(c == 'N')
			while(neues_spiel() == 1);
		else if(c == 'O')
			optionen();
		
		// Positionierung
		getmaxyx(stdscr, y, x);
		int links = (x/2) - 10;
		int oben = (y/2) - 6;
		
		// Menueausgabe
		clear();
		mvprintw(oben   , links, "++++++++++++++++++++");
		mvprintw(oben+1 , links, "+                  +");
		mvprintw(oben+2 , links, "+ N - Neues Spiel  +");
		mvprintw(oben+3 , links, "+                  +");
		mvprintw(oben+4 , links, "+ O - Optionen     +");
		mvprintw(oben+5 , links, "+                  +");
		mvprintw(oben+6 , links, "+ E - Ende         +");
		mvprintw(oben+7 , links, "+                  +");
		mvprintw(oben+8 , links, "+ Punkte: %3d      +", punkte);
		mvprintw(oben+9 , links, "+                  +");
		mvprintw(oben+10, links, "++++++++++++++++++++");
		
	// Ende bei ^X & E
	} while( (c=getch()) != 24 && c != 'E' && c != 'e');
	
	return 0;
}


void hangman_zeichnen(int leben, int y, int x)
{
	// Zeichne Teile des Galgens 
	// abhaengig von den verbleibenden Leben
	
	// Erdboden
	if(leben>=5)
		mvaddstr(y+9, x, "________");
	
	// Galgenboden
	if(leben<=4)
		mvaddstr(y+9, x, "/======\\");
	
	// Vertikaler Balken
	if(leben<=3){
		mvaddstr(y+0, x+2, "@");
		mvaddstr(y+1, x+2, "@");
		mvaddstr(y+2, x+2, "@");
		mvaddstr(y+3, x+2, "@");
		mvaddstr(y+4, x+2, "@");
		mvaddstr(y+5, x+2, "@");
		mvaddstr(y+6, x+2, "@");
		mvaddstr(y+7, x+2, "@");
		mvaddstr(y+8, x+1, "/@\\");
	}
	
	// Horizontaler Balken
	if(leben<=2){
		mvaddstr(y+0, x+3, "=====");
		mvaddstr(y+1, x+3, "/");
	}
	
	// Strick
	if(leben<=1){
		mvaddstr(y+1, x+5, "\\_/");
		mvaddstr(y+2, x+6, "|");
		mvaddstr(y+3, x+6, "|");
		mvaddstr(y+4, x+6, "$");
	}
	
	// Maennchen
	if(leben<=0) {
		mvaddstr(y+4, x+7, "o");
		mvaddstr(y+5, x+5, "-/-");
		mvaddstr(y+6, x+5, "/\\");
	}
}

void startbild()
{
	int y, x;
	int max_y, max_x;
	
	// Reinige Bildschirm
	clear();
	
	// Initiales Einlesen der Woerter
	lesen();
	
	// Positionierung berechen
	getmaxyx(stdscr, max_y, max_x);
	y=max_y/2-5;
	x=max_x/2-24;
	
	// Hangman auf rechte Seite zeichenen
	hangman_zeichnen(1, y, x+36);
	
	// Schriftzug zeichnen
	mvaddstr(y,x+11,"@");
	mvaddstr(y+1,x+11,"@");
	mvaddstr(y+2,x+11,"@");
	mvaddstr(y+3,x,"@@@\\ /@@@ @@@\\ /@@@\\  @@@\\ /@@@\\");
	mvaddstr(y+4,x,"@  @ @    @  @ @   @  @  @ @   @");
	mvaddstr(y+5,x,"@  @ @    @  @ @   @  @  @ @   @");
	mvaddstr(y+6,x,"@  @ \\@@@ @  @ \\@@@/@ @  @ \\@@@@");
	mvaddstr(y+7,x+31,"@");
	mvaddstr(y+8,x+28,"@@@@");
	
	mvaddstr(y+9, x+10, "Press ENTER...");
	
	
	// Return abwarten
	while(getch()!=10);
	
	// Bildschirm reinigen
	clear();
}


int neues_spiel()
{
	int i = 0,
		p = 5,
		r;
		
	char c,
		 o[20];
	
	// Letzte Zufallszahl
	static int lrand = -1;
	
	// Galgenbreite + Abstand
	const int manx = 16;
	
	// Zufallszahlengenerator initialisieren
	srand(time(NULL));
	
	/* Wenn die Liste Woerter enthaelt &
	 * bis die Zufallszahl eine andere als vorher ist
	 * 
	 * Hinweis: C bricht die Pruefung bei einer UND-Verknuepfung
	 * der Bedingungen ab, sobald eine Bedingung nicht zutrifft.
	 * Geprueft wird von links nach rechts. Daher verursacht der 
	 * Modulo-Operator in keinem Fall eine Division durch 0.
	 * 
	 * while((r = rand() % woerter) == lrand && woerter>0);
	 * kann daher eine Division durch 0 zur Folge haben
	 */
	while(woerter>0 && (r = rand() % woerter) == lrand);
	
	// Abbruch der Funktion bei 0 Woertern
	if(woerter<=0)
		return -1;
		
	// Reinige Bildschirm & zeichne Hangman
	clear();
	hangman_zeichnen(p, 1, 1);
	
	// Fuelle Ausgabe-String mit Platzhaltern und terminiere
	for(i=0;i<strlen(worte[r]);i++)
		o[i] = '-';
	o[i] = '\0';
	
	// Schreibe Eingabemaske
	mvprintw(1,manx,"Wort mit %2d Buchstaben: %s",strlen(worte[r]),o);
	mvprintw(3,manx, "Punkte: %3d", punkte);
	
	// Solange Leben verbleiben und weder ^R noch ^X eingegeben wurde
	while(p>0 && (c=getch())!= 18 && c!=24)
	{
		// Reinige Bildschirm
		clear();
		
		// Wenn das Zeichen ein Buchstabe ist
		if(isalpha((int)c))	{
			// Wandle Zeichen in Grossbuchstaben um
			c = toupper(c);	
			
			// Spiele Zeichen und berechne verbleibende Leben
			// Zeichne aktuellen Hangman
			hangman_zeichnen((p = p - spielen(c, worte[r], o)), 1, 1);
		}
		
		// Wenn das Zeichen kein Buchstabe ist
		else
		{
			// Gebe Fehlermeldung, Hilfe und Hangman aus
			mvprintw(4,manx, "Es werden nur Buchstaben akzeptiert");
			mvprintw(5,manx, "Neustart mit STRG+R");
			mvprintw(6,manx, "Beenden mit STRG+X");
			hangman_zeichnen(p, 1, 1);
		}
		
		// Schreibe Eingabemaske
		mvprintw(1,manx,"Wort mit %2d Buchstaben: %s", strlen(worte[r]), o);
		mvprintw(3,manx, "Punkte: %3d", punkte);
		
		// Beende die Schleife wenn das Wort geloest wurde
		if(spielstand(o)==0)
			break;
	}
	
	// Wenn das Wort nicht geloest wurde
	if(p<=0)
	{
		// Gebe Loesung und Hinweis  aus
		mvprintw(1,manx,"Wort mit %2d Buchstaben: %s", strlen(worte[r]), worte[r]);
		mvprintw(5,manx, "YOU LOST!");
		// Berechne Punkte
		punkte -= 2;
	}
	// Wenn das Wort geloest wurde
	else if(spielstand(o)==0)
	{
		// Gebe Hinweis aus
		mvprintw(5,manx, "YOU WON!");
		// Berechne Punkte
		punkte += p;
	}
	
	// Gebe Hilfe und aktuelle Punktzahl aus
	mvprintw(3,manx, "Punkte: %3d", punkte);
	mvprintw(6,manx, "Neustart mit R");
	mvprintw(7,manx, "Beenden mit beliebiger Taste");
	
	// Warte Eingabe ab
	c = getch();
	
	// Reinige Bildschirm
	clear();
	
	// Speichere Index des gespielten Wortes
	lrand=r;
	
	// Wenn ^R oder R eingegeben wurde beende mit 1
	if(c == 18 || c == 'r' || c == 'R')
		return 1;
	
	// Beende mit 0
	return 0;
}

int spielen(char c, char* s, char* o)
{
	int i = 0,
		r = 1;
		
	// Bis zum Ende des Strings
	for(i=0;s[i]!='\0';i++)
		// Wenn der Buchstabe im Wort vorkommt
		if(s[i]==c) {
			// Setze Rueckgabewert auf 0
			r = 0;
			// Ersetze Platzhalter im Output-String durch Buchstabe
			o[i] = c;
		}
	
	return r;
}

int spielstand(char* s)
{
	int i = 0, b = 0;
	for(i=0;s[i]!='\0';i++)
		if(s[i]=='-')
			b++;
	return b;
}

	
void optionen()
{
	int y, x;
	char c = 0;
	
	do
	{
		// Positionierung
		getmaxyx(stdscr, y, x);
		int oben = (y/2) - 9,
			links = (x/2) - 15;
		
		// Wenn das Zeichen ein Buchstabe ist
		if(isalpha(c))
			// Wandle in Grossbuchstabe um
			c = toupper(c);

		// N - Neues Wort eingeben
		if(c=='N')
			wort_eingeben();
			
		// W - Wortliste anzeigen
		else if(c=='W')
			wortliste();
		
		// L - Wort loeschen
		else if(c=='L')
			wort_loeschen();
			
		// R - Woerter neu laden
		else if(c == 'R')
			lesen();
			
		// P - Punkte zuruecksetzen
		else if(c == 'P')
			punkte = 0;
		
		// S - Speichern & Hauptmenue	
		else if(c == 'S' && speichern()==0)	{
				clear();
				break;
		}
		
		// Reinige Bildschirm
		clear();
		
		// Gebe Menue aus
		mvprintw(oben   , links, "++++++++++++++++++++++++++++++");
		mvprintw(oben+1 , links, "+                            +");
		mvprintw(oben+2 , links, "+ N - Neues Wort eingeben    +");
		mvprintw(oben+3 , links, "+                            +");
		mvprintw(oben+4 , links, "+ W - Wortliste anzeigen     +");
		mvprintw(oben+5 , links, "+                            +");
		mvprintw(oben+6 , links, "+ L - Wort loeschen          +");
		mvprintw(oben+7 , links, "+                            +");
		mvprintw(oben+8 , links, "+ R - Woerter neu laden      +");
		mvprintw(oben+9 , links, "+                            +");
		mvprintw(oben+10, links, "+ P - Punkte zuruecksetzen   +");
		mvprintw(oben+11, links, "+                            +");
		mvprintw(oben+12, links, "+ S - Speichern & Hauptmenue +");
		mvprintw(oben+13, links, "+                            +");
		mvprintw(oben+14, links, "+ E - Hauptmenue             +");
		mvprintw(oben+15, links, "+                            +");
		mvprintw(oben+16, links, "+ Punkte: %3d | Woerter: %3d +",punkte,woerter);
		mvprintw(oben+17, links, "++++++++++++++++++++++++++++++");

	// Solange Zeichen nicht ^X oder E ist
	} while((c = getch()) != 24 && c != 'E' && c != 'e');
}

int lesen()
{
	int i;
	
	// Anzahl der Woerter zuruecksetzen
	woerter = 0;
	
	// Datei Read-Only oeffnen
	FILE* f = fopen("liste.txt", "r");
	// Funktionsabbruch wenn die Datei nicht gelesen werden konnte
	if(f==NULL)
		return 0;
	
	do {
		i = 0;
		
		// Lese Zeichen ein und wandle es in Grossbuchstabe um
		// Solange ein Buchstabe ist zaehle i hoch
		while( isalpha( worte[woerter][i] = toupper( fgetc(f) ) ) )
		{ i++; }
		
		// Wenn das naechste Zeichen EOF ist, beende die Schleife
		if(worte[woerter][i] == EOF)
			break;
		
		// Wenn das naechste Zeichen nicht \n ist
		else if(worte[woerter][i]!=10)
			// Verwerfe bis zum Ende der Zeile
			while(fgetc(f)!=10);
		
		// Terminiere String
		worte[woerter][i]='\0';
		
		// Zaehle ein Wort dazu
		woerter++;
		
	// Solange die Anzahl der Worte kleiner als das Maximum ist
	} while(woerter<MAXWORTE);
	
	// Schliesse Datei
	fclose(f);
	
	// Gebe Anzahl der eingelesenen Woerter zurueck
	return woerter;
}

int speichern()
{
	int i=0,
		j;
	
	// Datei schreibbar oeffnen
	FILE *f = fopen("liste.txt", "w");
	
	// Reinige Bildschirm
	clear();
	
	// Wenn Datei nicht geoeffnet ist
	if(f==NULL)
	{
		// Gebe Fehlermeldung aus
		mvprintw(1,1, "liste.txt konnte nicht zum schreiben geoeffnet werden");
		
		// Wenn Datei lesbar ist, gebe Read-Only-Hinweis aus
		if(fopen("liste.txt", "r")!=NULL)
			mvprintw(2,1, "Ist die Datei Read-Only?");
		// Sonst gebe Pfad-Hinweis aus
		else
			mvprintw(2,1, "Ist der Pfad verfuegbar?");
			
		// Warte auf Eingabe und Funktionsabbruch
		mvprintw(3,1, "Zurueck mit beiebiger Taste");
		getch();
		return 1;
	}
	
	else
	{
		// Jedes Wort durchlaufen
		for(i=0;i<woerter;i++) {
			// Jedes Zeichen durchlaufen
			for(j=0;worte[i][j]!='\0';j++)
				// Zeichen schreiben
				fputc(worte[i][j], f);
			// Neue Zeile am Ende des Wortes
			fputc('\n', f);
		}
		
		// Hinweis ausgeben und Eingabe abwarten
		mvprintw(1,1, "%d Woerter geschrieben", woerter);
		mvprintw(2,1, "Weiter mit beliebiger Taste");
		getch();
	}
	
	// Datei schliessen und Funktionsende
	fclose(f);
	return 0;
}


void wort_eingeben()
{
	char s[20],
		 c = 0;
	int i = 0;
	
	// Reinige Bildschirm und gebe Eingabemaske aus
	clear();
	mvprintw(1,1,"Wort eingeben: ");

	// Lese Zeichen ein
	// Bis Zeichen \n ist
	for(i=0;(c = getch())!=10;i++) {
		
		// Wenn das Zeichen ein Buchstabe ist
		if(isalpha(c)) {
			// Fuege es als Grossbuchstaben an den String an
			s[i] = toupper(c);
			// Terminiere String neu
			s[i+1] = '\0';
		}
		
		// Gebe String aus
		mvprintw(1,1,"Wort eingeben: %s",s);
	}
	
	// Wenn der String Zeichen enthaelt
	if(strlen(s)) {
		
		// Kopiere den String in die Wortliste
		strcpy(worte[woerter], s);
		
		// Erhoehe Woerteranzahl
		woerter++;
	}
}

void wortliste()
{
	int y,x,
		i = 0,
		offset = 3;
	
	// Reinige Bildschirm und lese Festergroesse ein
	clear();
	getmaxyx(stdscr,y,x);
	
	// Gebe Kopfzeile aus
	mvprintw(1,1,"Folgende Wörter befinden sich im Speicher:");
	
	// Jedes Wort
	for(i=0;i<woerter;i++)
	{
		// Wenn das Wort zu wenig Abstand zum Fensterboden hat
		if((offset+i+2)%y==0)
		{
			// Warte auf Eingabe und rechne zusaetzliche Zeilen dazu
			mvprintw(y-1,1, "Naechste Seite mit beliebiger Taste");
			getch();
			offset += 5;
			
			// Reinige Bildschirm und gebe neue Kopfzeile aus
			clear();
			mvprintw(1,1,"Folgende Wörter befinden sich im Speicher:");
		}
		
		// Gebe Wort aus
		mvprintw((offset+i)%y,2,"%2d - %s", i+1, worte[i]);
	}
	
	// Warte auf Eingabe
	mvprintw((offset+i+1)%y,1,"Weiter mit beliebiger Taste");
	getch();
}

void wort_loeschen()
{
	int i,
		index=0;
	char c,
		 s[20];
	
	// Reinige Bildschirm und Eingabeaufforderung
	clear();
	mvprintw(1,1, "Index des zu löschenden Wortes: ");
	
	// Solange die Eingabe nicht \n ist
	while((c=getch()) != 10) {
		
		// Wenn die Eingabe eine Zahl ist
		if(isdigit(c)) {
			
			// Betrachte die Zahl als letzte Stelle des Index
			index = (index*10) + (c-48);
			// Gebe den Index aus
			mvprintw(1,34,"%2d",index);
		}
	}
	
	// Ziehe 1 ab um von 0 an zu zaehlen
	index--;

	// Wenn der Index gueltig ist
	if(index<woerter) {
		
		// Kopiere das zu loeschende Wort in einen temporaeren String
		strcpy(s, worte[index]);
		
		// Jedes nachfolgede Wort
		for(i=index;i<woerter;i++)
			// Wird eine Position nach vorne verschoben
			strncpy(worte[i], worte[i+1],20);
		
		// Reduziere Woerteranzahl
		woerter--;
		
		// Zeige gelöschtes Wort an
		mvprintw(2,1, "Gelöschtes Wort: %s", s);
	}
	
	// Sonst Fehlermeldung
	else
		mvprintw(2,1, "Es existiert kein Wort mit diesem Index!");
	
	// Warte auf Eingabe
	mvprintw(3,1, "Weiter mit beliebiger Taste");
	getch();
}
