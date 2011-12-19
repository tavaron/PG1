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

#define MAXWORDS 100


int drawHangman(int left, int yshift, int xshift);
int splashScreen();
int newGame();
int getWord();
int read_liste();
int checkLetter(char c, char* s, char* o);
int spielstand(char* s);
void setWord(char* s);
int optionen();
void printOMenu(int ceiling, int left);
void wortEingeben();
void wortliste();
void wortloeschen();
int speichern();
int toupper();
int isalpha();
int isdigit();

int woerter = 0, lastrand = -1, punkte = 0;
char words[MAXWORDS][20];

int main(int argc, char** argv)
{
	char c;
	initscr();
	curs_set(0);
	noecho();
	atexit((void*)endwin);
	
	int y, x;
	getmaxyx(stdscr, y, x);
	if(y<24||x<80) {
		mvprintw(0, 0, "Terminal zu klein!");
		mvprintw(1, 0, "80x24 erforderlich!");
		mvprintw(2, 0, "Beende Programm...");
		return(1);
	}
	
	c = splashScreen();
	do
	{
		c = toupper(c);
		if(c == 'N')
			while(newGame() == 1);
		else if(c == 'O')
			while(optionen() == 1);
		
		
		getmaxyx(stdscr, y, x);
		int left = (x/2) - 10;
		int ceiling = (y/2) - 6;
		wclear(stdscr);
		
		mvprintw(ceiling   , left, "++++++++++++++++++++");
		mvprintw(ceiling+1 , left, "+                  +");
		mvprintw(ceiling+2 , left, "+ N - Neues Spiel  +");
		mvprintw(ceiling+3 , left, "+                  +");
		mvprintw(ceiling+4 , left, "+ O - Optionen     +");
		mvprintw(ceiling+5 , left, "+                  +");
		mvprintw(ceiling+6 , left, "+ E - Ende         +");
		mvprintw(ceiling+7 , left, "+                  +");
		mvprintw(ceiling+8 , left, "+ Woerter: %2d      +", woerter);
		mvprintw(ceiling+9 , left, "+                  +");
		mvprintw(ceiling+10, left, "++++++++++++++++++++");
		
		refresh();
	}while( (c=getch()) != 24 && c != 'E' && c != 'e');
	
	return 0;
}

int splashScreen()
{
	int y, x;
	int max_y, max_x;
	
	clear();
	drawHangman(1, 0, 15);
	read_liste();
	getmaxyx(stdscr, max_y, max_x);
	y=max_y/2-5;
	x=max_x/2-24;
	
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
	
	
	refresh();
	while(getch()!=10);
	clear();
	return 0;
}

int drawHangman(int left, int yshift, int xshift)
{
	int y, x;
	int max_y, max_x;
	
	getmaxyx(stdscr,max_y, max_x);
	if(max_y<14||max_x<10) {
		mvwprintw(stdscr, 0, 0, "Fenster zu klein!");
		return 1;
	}
	
	y=max_y/2-5+yshift;
	x=max_x/2-4+xshift;
	if(left<=4){
		mvwaddstr(stdscr, y+9, x, "/======\\");
	}
	if(left<=3){
		mvwaddstr(stdscr, y+0, x+2, "@");
		mvwaddstr(stdscr, y+1, x+2, "@");
		mvwaddstr(stdscr, y+2, x+2, "@");
		mvwaddstr(stdscr, y+3, x+2, "@");
		mvwaddstr(stdscr, y+4, x+2, "@");
		mvwaddstr(stdscr, y+5, x+2, "@");
		mvwaddstr(stdscr, y+6, x+2, "@");
		mvwaddstr(stdscr, y+7, x+2, "@");
		mvwaddstr(stdscr, y+8, x+1, "/@\\");
	}
	if(left<=2){
		mvwaddstr(stdscr, y+0, x+3, "=====");
		mvwaddstr(stdscr, y+1, x+3, "/");
	}
	if(left<=1){
		mvwaddstr(stdscr, y+1, x+5, "\\_/");
		mvwaddstr(stdscr, y+2, x+6, "|");
		mvwaddstr(stdscr, y+3, x+6, "|");
		mvwaddstr(stdscr, y+4, x+6, "$");
	}
	if(left<=0) {
		mvwaddstr(stdscr, y+4, x+7, "o");
		mvwaddstr(stdscr, y+5, x+5, "-/-");
		mvwaddstr(stdscr, y+6, x+5, "/\\");
	}
	refresh();
	return 0;
}

int read_liste()
{
	woerter = 0;
	FILE* f = fopen("liste.txt", "r");
	
	do {
		int i = 0;
		while( ((words[woerter][i] = toupper(fgetc(f)))!= 10 && words[woerter][i] != EOF && 	((words[woerter][i] >= 65 && words[woerter][i] <= 90) || (words[woerter][i] >= 97 && words[woerter][i] <= 122)) ))
		{ i++; }
		if(words[woerter][i] == EOF)
			break;
		else if(words[woerter][i]!=10)
			while(fgetc(f)!=10);
		words[woerter][i]='\0';
		//printw("%s\n", words[woerter]);
		woerter++;
	} while(woerter<MAXWORDS);
	fclose(f);
	return woerter;
}

int getWord()
{
	srand(time(NULL));

	if(woerter==0)
		return -1;

	return (rand() % woerter);
}

void setWord(char* s)
{
	int i = 0;
	for(i=0;s[i]!='\0';i++)
		words[woerter][i] = s[i];
	woerter++;
}

int newGame()
{
	int i = 0, p = 5, r;

	while((r = getWord()) == lastrand);
	
	if(r==-1)
		return -1;
		
	char c;
	char o[20];
	
	
	clear();
	drawHangman(p, 0, 0);
	
	
	for(i=0;i<strlen(words[r]);i++)
		o[i] = '-';
	o[i] = '\0';
	mvprintw(1,1,"Wort mit %2d Buchstaben: %s",strlen(words[r]),o);
	mvprintw(3,1, "Punkte: %3d", punkte);
	refresh();
	
	while(p>0 && (c=getch())!= 18 && c!=24)
	{
		clear();
		mvprintw(3,1, "Punkte: %3d", punkte);
		if(isalpha((int)c))
		{
			c = toupper(c);	
			drawHangman((p = p - checkLetter(c, words[r], o)), 0, 0);
		}
		else
		{
			mvprintw(4,1, "Es werden nur Buchstaben akzeptiert");
			mvprintw(5,1, "Neustart mit STRG+R");
			mvprintw(6,1, "Beenden mit STRG+X");
			drawHangman(p, 0, 0);
		}
		mvprintw(1,1,"Wort mit %2d Buchstaben: %s",strlen(words[r]),o);
		if(spielstand(o)==0)
			break;
	}
	
	if(p<=0)
	{
		mvprintw(1,1,"Wort mit %2d Buchstaben: %s",strlen(words[r]),words[r]);
		mvprintw(5,1, "YOU LOST!");
		mvprintw(6,1, "Neustart mit STRG+R");
		mvprintw(7,1, "Beenden mit STRG+X");
		punkte -= 2;
		mvprintw(3,1, "Punkte: %3d", punkte);
		c = getch();
	}
	else if(spielstand(o)==0)
	{
		mvprintw(5,1, "YOU WON!");
		mvprintw(6,1, "Neustart mit STRG+R");
		mvprintw(7,1, "Beenden mit STRG+X");
		punkte += p;
		mvprintw(3,1, "Punkte: %3d", punkte);
		c = getch();
	}
	clear();
	lastrand=r;
	if(c==18)
		return 1;
	return 0;
}

int checkLetter(char c, char* s, char* o)
{
	int i = 0, b = 1;
	for(i=0;s[i]!='\0';i++)
		if(s[i]==c)
		{
			b = 0;
			o[i] = c;
		}
	return b;
}

int spielstand(char* s)
{
	int i = 0, b = 0;
	for(i=0;s[i]!='\0';i++)
		if(s[i]=='-')
			b++;
	return b;
}
		
int optionen()
{
	int y, x;
	char c;
	getmaxyx(stdscr, y, x);
	
	clear();
	printOMenu((y/2) - 7, (x/2) - 15);
	
	while((c = getch()) != 15 && c != 24 && c != 'E' && c != 'e')
	{
		if(isalpha(c))
			c = toupper(c);

		if(c=='N')
			wortEingeben();
		else if(c=='W')
			wortliste();
		else if(c=='L')
			wortloeschen();
		else if(c == 'S')
		{
			speichern();
			clear();
			break;
		}
		clear();
		printOMenu((y/2) - 7, (x/2) - 15);

		
	}
	if(c==15)
		return 1;
	return 0;
}

void printOMenu(int ceiling, int left)
{
	mvprintw(ceiling   , left, "++++++++++++++++++++++++++++++");
	mvprintw(ceiling+1 , left, "+                            +");
	mvprintw(ceiling+2 , left, "+ N - Neues Wort eingeben    +");
	mvprintw(ceiling+3 , left, "+                            +");
	mvprintw(ceiling+4 , left, "+ W - Wortliste anzeigen     +");
	mvprintw(ceiling+5 , left, "+                            +");
	mvprintw(ceiling+6 , left, "+ L - Wort loeschen          +");
	mvprintw(ceiling+7 , left, "+                            +");
	mvprintw(ceiling+8 , left, "+ R - Woerter neu laden      +");
	mvprintw(ceiling+9 , left, "+                            +");
	mvprintw(ceiling+10, left, "+ S - Speichern & Hauptmenue +");
	mvprintw(ceiling+11, left, "+                            +");
	mvprintw(ceiling+12, left, "+ E - Hauptmenue             +");
	mvprintw(ceiling+13, left, "+                            +");
	mvprintw(ceiling+14, left, "++++++++++++++++++++++++++++++");
}

void wortEingeben()
{
	char s[20], c = 0;
	int i = 0;
	s[0] = '\0';
	clear();
	mvprintw(1,1,"Wort eingeben: %s",s);
	while(1)
	{
		c = getch();
		if(c==10)
			break;
		else if(isalpha(c))
		{
			s[i] = toupper(c);
			i++;
			s[i] = '\0';
		}
		mvprintw(1,1,"Wort eingeben: %s",s);
	}
	if(strlen(s)>0)
		setWord(s);
}

void wortliste()
{
	int y,x;
	int i = 0;
	int offset = 3;
	
	clear();
	getmaxyx(stdscr,y,x);
	mvprintw(1,1,"Folgende Wörter befinden sich im Speicher:");
	
	for(i=0;i<woerter;i++)
	{
		if((offset+i+2)%y==0)
		{
			mvprintw(y-1,1, "Naechste Seite mit beliebiger Taste");
			getch();
			offset += 5;
			
			clear();
			mvprintw(1,1,"Folgende Wörter befinden sich im Speicher:");
		}
		mvprintw((offset+i)%y,2,"%2d - %s", i, words[i]);
	}
	mvprintw((offset+i+1)%y,1,"Weiter mit beliebiger Taste");
	getch();
}

void wortloeschen()
{
	int index=0;
	char c;
	clear();
	mvprintw(1,1, "Index des zu löschenden Wortes: ");
	while((c=getch()) != 10)
	{
		if(isdigit(c))
		{
			index= (index*10) + (c-48);
			mvprintw(1,34,"%2d",index);
		}
	}
	//mvprintw(1,1, "Index des zu löschenden Wortes: %d", index);
	int i;
	char s[20];
	if(index<woerter)
	{
		strncpy(s, words[index], 20);
		for(i=index;i<woerter;i++)
			strncpy(words[i], words[i+1],20);
		woerter--;
		mvprintw(2,1, "Gelöschtes Wort: %s", s);
	}
	else
		mvprintw(2,1, "Es existiert kein Wort mit diesem Index!");
		
	mvprintw(1,1, "Index des zu löschenden Wortes: %2d", index);
	mvprintw(3,1, "Weiter mit beliebiger Taste");
	getch();
}

int speichern()
{
	int i,j;
	FILE *f = fopen("liste.txt", "w");
	clear();
	if(f==NULL)
	{
		mvprintw(1,1, "liste.txt konnte nicht zum schreiben geoeffnet werden");
		mvprintw(2,1, "Ist die Datei Read-Only?");
		mvprintw(3,1, "Zurueck mit beiebiger Taste");
		getch();
		return 1;
	}
	else
	{
		for(i=0;i<woerter;i++)
		{
			for(j=0;words[i][j]!='\0';j++)
				fputc(words[i][j], f);
			fputc('\n', f);
		}
			
		mvprintw(1,1, "%2d Woerter geschrieben", woerter);
		mvprintw(2,1, "Weiter mit beliebiger Taste");
		fclose(f);
		getch();
	}
	return 0;
}
