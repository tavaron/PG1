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

int main(int argc, char** argv)
{
	while(1) {
		short correct = 0;
		char menu;
		char c;
		printf("Bitte wählen Sie:\n\n");
		printf("1 - neuen Teilnehmer anlegen\n");
		printf("2 - Telefonliste ausgeben\n");
		printf("3 - Teilnehmer löschen\n");
		printf("4 - Programm beenden\n\n");
		printf("Auswahl: ");
		
		while((c=getchar())!=10) {
			if(c>=49&&c<=52) {
				menu = c;
				correct = 1;
			}
		}
		
		printf("\n");
		
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
	while(1) {
		int i = 0;
		
		for(i=0;i<MAX_EINTRAEGE;i++)
			if(liste[i].name[0]=='\0')
				break;
		if(i==MAX_EINTRAEGE - 1) {
			printf("Die Liste ist bereits voll!\n\n");
			break;
		}
		else {
			printf("Sie erstellen nun Eintrag Nr. %d\n", i+1);
			printf("Bitte geben Sie den Namen ein: ");
			scanf("%s", liste[i].name);
			printf("Bitte geben Sie den Vornamen ein: ");
			scanf("%s", liste[i].vorname);
			printf("Bitte geben Sie die Nummer ein: ");
			scanf("%s", liste[i].nummer);
			printf("Der Eintrag wurde erstellt...\n\n");
			break;
		}
		while(getchar()!=10);
	}
}

void ausgabe()
{
	int i = 0,
		j = 0,
		k = 0;
	ausgabeHeader();
	for(i=0;i<MAX_EINTRAEGE;i++)
			if(liste[i].name[0]=='\0')
				break;
	for(j=0;j<=i;j++) {
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
}

void loeschen()
{}

void ausgabeHeader()
{
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
