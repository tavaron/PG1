//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		15.11.2011 v0.1
//      geaendert:	15.11.2011
//      
//      Beschreibung: !!!
//      
//      Eingabe: !!!
//      
//      Ausgabe: !!!
//      
//      ------------------------------------------------------------------------


#include <stdio.h>

struct eintrag {
	char name[40];
	char vorname[20];
	char nummer[20];
}
struct eintrag liste[20];

void eingabe();
void ausgabe();
void loeschen();

int main(int argc, char** argv)
{
	while(1) {
		short correct = 1;
		char menu = EOF;
		printf("Bitte wählen Sie:\n\n");
		printf("1 - neuen Teilnehmer anlegen\n");
		printf("2 - Telefonliste ausgeben\n");
		printf("3 - Teilnehmer löschen\n");
		printf("4 - Programm beenden\n\n");
		printf("Auswahl: ");
		
		while((menu=getchar())<49||menu>52)
		{ correct = 0; }
		
		printf("\n");
		
		if(correct) {
			if(menu == 1)
				eingabe();
			else if(menu == 2)
				ausgabe();
			else if(menu == 3)
				loeschen();
			else if(menu == 4)
				break;
		}
	}
	printf("Exit...\n");
	return 0;
}

void eingabe()
{}

void ausgabe()
{}

void loeschen()
{}
