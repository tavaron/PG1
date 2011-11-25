//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:       Marius Christ
//      Matr.-Nr.:  954402
//      Datum:      15.11.2011 v0.1
//      geaendert:  15.11.2011
//      
//      Beschreibung: verwaltet eine telefonliste in einem array
//      
//      Eingabe: menuepunkte, eintraege
//      
//      Ausgabe: menue, liste
//      
//      ------------------------------------------------------------------------


#include <stdio.h>

#define NAME_LENGTH 40
#define VORNAME_LENGTH 20
#define NUMMER_LENGTH 20
#define MAX_EINTRAEGE 20

struct eintrag {
    char name[NAME_LENGTH];
    char vorname[VORNAME_LENGTH];
    char nummer[NUMMER_LENGTH];
};
struct eintrag liste[MAX_EINTRAEGE];

void eingabe();
void ausgabe();
void ausgabeHeader();
void loeschen();
void spaces(int anzahl);
int anzahlEintraege();

int main(int argc, char** argv)
{
    // bis manueller Schleifenabbruch
    while(1) {
		
        short correct = 0;
        char menu;
        char c;
        
        // Hauptmenü ausgeben
        printf("Bitte wählen Sie:\n\n");
        printf("1 - neuen Teilnehmer anlegen\n");
        printf("2 - Telefonliste ausgeben\n");
        printf("3 - Teilnehmer löschen\n");
        printf("4 - Programm beenden\n\n");
        printf("Auswahl: ");
        
        // Puffer leeren und Eingabe prüfen
        while((c=getchar())!=10) {
            if(c>=49&&c<=52) {
                menu = c;
                correct = 1;
            }
        }
        
        printf("\n");
        
        // Wenn eine korrekte Eingabe gemacht wurde, rufe passende Funktion auf
        if(correct) {
            if(menu == '1')
                eingabe();
            else if(menu == '2')
                ausgabe();
            else if(menu == '3')
                loeschen();
            else if(menu == '4')
                break;
        }
    }
    printf("Exit...\n");
    return 0;
}

void eingabe()
{
	int i = anzahlEintraege();
	// Wenn Liste voll
	if(i==MAX_EINTRAEGE - 1)
		printf("Die Liste ist bereits voll!\n\n");
	// sonst
	else {
		// Eingabeaufforderung und Einlesen
		printf("Sie erstellen nun Eintrag Nr. %d\n", i+1);
		printf("Bitte geben Sie den Namen ein: ");
		scanf("%s", liste[i].name);
		printf("Bitte geben Sie den Vornamen ein: ");
		scanf("%s", liste[i].vorname);
		printf("Bitte geben Sie die Nummer ein: ");
		scanf("%s", liste[i].nummer);
		printf("Der Eintrag wurde erstellt...\n\n");
	}
    // Eingabepuffer leeren
    while(getchar()!=10);
}

void ausgabe()
{
    int j = 0,
        k = 0;
    ausgabeHeader();

	// für jeden Eintrag
    for(j=0;j<anzahlEintraege();j++) {
		
		// Positionsnummer ausgeben
        if(j>=99)
            printf("%d ",j+1);
        else if(j>=9)
            printf("%d  ",j+1);
        else
            printf("%d   ",j+1);
            
        // Ausgabe der Eintraege
        for(k=0;liste[j].name[k]!='\0';k++)
            putchar(liste[j].name[k]);
        spaces(NAME_LENGTH-k+1);
        for(k=0;liste[j].vorname[k]!='\0';k++)
            putchar(liste[j].vorname[k]);
        spaces(VORNAME_LENGTH-k+1);
        for(k=0;liste[j].nummer[k]!='\0';k++)
            putchar(liste[j].nummer[k]);
        printf("\n");
    }
    printf("\n");
}

void loeschen()
{
    int index = 0,
        i = 0;
    
    // Eingabeauforderung und Einlesen
    printf("Bitte geben Sie die Nummer des Eintrags an: ");
    scanf("%d", &index);
    i = index - 1;
    
    // Eingabepuffer leeren
    while(getchar()!=10);
    
    // Einträge aufrücken und dabei zu löschenden Eintrag überschreiben
    for(;i<=anzahlEintraege();i++)
        liste[i]=liste[i+1];
    
    printf("Der Eintrag Nr. %d wurde gelöscht...\n\n", index);
}

void ausgabeHeader()
{
    printf("Nr. ");
    printf("Name");
    spaces(NAME_LENGTH - 3);
    printf("Vorname");
    spaces(VORNAME_LENGTH - 6);
    printf("Nummer\n");
}

void spaces(int anzahl)
{
    int i = 0;
    for(;i<anzahl;i++)
        putchar(' ');
}

int anzahlEintraege()
{
    int i = 0;
    // zähle hoch, bis Name leer ist
    for(i=0;i<MAX_EINTRAEGE;i++)
            if(liste[i].name[0]=='\0')
                break;
    return i;
}
