//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:       Marius Christ
//      Matr.-Nr.:  954402
//      Datum:      15.11.2011 v0.1
//      geaendert:  15.11.2011
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

#define NAME_LENGTH 40
#define VORNAME_LENGTH 20
#define NUMMER_LENGTH 20

struct eintrag {
    char name[NAME_LENGTH];
    char vorname[VORNAME_LENGTH];
    char nummer[NUMMER_LENGTH];
    // Zeiger auf den nächsten struct
    struct eintrag *next;
};
// Listenkopf und -ende
struct eintrag *anfang, *ende;

// Prototypen
void eingabe();
void ausgabe();
void loeschen();
void init();
void spaces(int anzahl);
void ausgabeHeader();

int main(int argc, char** argv)
{
	// initialisiere Liste
	init();
	
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

void init()
{
	// reserviere Speicher
	anfang = (struct eintrag*) malloc(sizeof(struct eintrag));
	ende = (struct eintrag*) malloc(sizeof(struct eintrag));
	
	// Wenn Speicher nicht reserviert werden konnte
	if(anfang == NULL || ende == NULL)
	{
		// werfe Fehler und beende mit Errorcode 1
		printf("Speicherplatzmangel...\n");
		exit(1);
	}
	// verkette Anfang mit Ende und baue Schleife am Ende
	anfang->next = ende->next = ende;
}

void eingabe()
{
	struct eintrag *element, *tmp;
	// Speicher für neues Element reservieren
	element = (struct eintrag*) malloc(sizeof(struct eintrag));
	
	// Wenn Speicher nicht reserviert werden konnte
	if(element == NULL)
	{
		// werfe Fehler und beende mit Errorcode 1
		printf("Speicherplatzmangel...\n");
		exit(1);
	}
	
	// Eingabeaufforderung und Einlesen
	printf("Neuer Eintrag wird angelegt...\n");
	printf("Name: ");
	scanf("%s", element->name);
	printf("Vorname: ");
	scanf("%s", element->vorname);
	printf("Nummer: ");
	scanf("%s", element->nummer);
	printf("\n");
	// Eingabepuffer leeren
	while(getchar()!=10);
	
	// Erstes Element zwischenspeichern
	tmp = anfang->next;
	// Neues Element am Anfang einfügen
	anfang->next = element;
	// zwischengespeichertes Element mit neuem Element verketten
	element->next = tmp;
}

void ausgabe()
{
	int i = 1,k;
	struct eintrag *_eintrag;
	// _eintrag mit erstem Element initialisieren
	_eintrag = anfang->next;
	
	ausgabeHeader();
	
	// solange ende nicht erreicht
	while(_eintrag != ende)
	{
		// Positionsnummer ausgeben
		if(i>=100)
            printf("%d ",i);
        else if(i>=10)
            printf("%d  ",i);
        else
            printf("%d   ",i);
            
        // Ausgabe der Eintraege
        for(k=0;_eintrag->name[k]!='\0';k++)
            putchar(_eintrag->name[k]);
        spaces(NAME_LENGTH-k+1);
        for(k=0;_eintrag->vorname[k]!='\0';k++)
            putchar(_eintrag->vorname[k]);
        spaces(VORNAME_LENGTH-k+1);
        for(k=0;_eintrag->nummer[k]!='\0';k++)
            putchar(_eintrag->nummer[k]);
        printf("\n");
        
        // zum nächsten Eintrag wechseln
		_eintrag = _eintrag->next;
		
		// Positionsnummer hochzählen
		i++;
	}
	printf("\n");
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

void loeschen()
{
	int index, i = 1;
	
	// temporären Zeiger anlegen
	struct eintrag *tmp;
	
	// tmp-Zeiger auf Anfang der Liste setzen
	tmp = anfang;
	
	// Nr. abfragen
	printf("Nr. des zu löschenden Eintrags: ");
	scanf("%d", &index);
	printf("\n");
	// Eingabepuffer leeren
	while(getchar()!=10);
	
	// Liste durchlaufen bis zum angegebenen Eintrag
	for(;i<=index;i++)
	{
		// beim erreichen des Eintrags
		if(i==index)
		{
			// Speicher freigeben
			free(tmp->next);
			// Verkettung anpassen
			tmp->next = tmp->next->next;
		}
		// Einen Eintrag weitergehen
		tmp = tmp->next;
	}
}
