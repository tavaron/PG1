//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		08.11.2011 v1.0
//      geaendert:	08.11.2011
//      
//      Beschreibung: 	liest text in eine datei ein, erstellt diese bei
//						bedarf, fragt ob ueberschrieben werden soll und
//						gibt diese auf wunsch aus.
//      
//      Eingabe:	text, j|n
//      
//      Ausgabe:	eingabeaufforderung, fehler, dateioperationen, text
//      
//      ------------------------------------------------------------------------


#include <stdio.h>

int main(int argc, char** argv)
{
	char path[150];
	FILE *f;
	char c;
	
	//Widerhole
	while(1) {
		// Dateiabfrage
		printf("In welcher Datei soll der Text gespeichert werden?\n");
		// lese dateipfad ein
		scanf("%s",path);
		// Reinige stdin
		while(getchar()!=10);
		printf("\n");
		
		// wenn datei nicht existiert
		if(fopen(path, "r") == NULL) {
			// erstelle datei
			printf("Datei wird erstellt...\n");
			f = fopen(path, "w+");
			// wenn pfad ungueltig
			if(f == NULL) {
				printf("\nDatei konnte nicht angelegt werden!\n");
				while(getchar()!=10);
				// nochmal
				continue;
			}
		}
		else {
			// nochmal
			while(1) {
				//ueberschreiben?
				printf("Datei existiert! Überschreiben? (j|n) ");
				scanf("%c", &c);
				while(getchar()!=10);
				// wenn ja
				if(c=='j') {
					// oeffne mit schreibzugriff
					f = fopen(path, "w+");
					printf("Datei wird überschrieben!\n");
					//beende schleife
					break;
				}
				// wenn nicht
				else if(c=='n') {
					// anhaengen
					f = fopen(path, "a+");
					printf("Text wird angehängt\n");
					// beende schleife
					break;
				}
			}
		}
		// Furt He
		break;
	}
	// puffer stdin leeren
	while(getchar()!=10);
	
	printf("Bitte geben Sie nun den Text ein:\n");
	//erster durchlauf
	short firstrun = 1;
	while(1) {
		// temp Vars
		char _C;
		char __C;
		// beim ersten durchlauf
		if(firstrun) {
			__C = -1;
			_C = -1;
		}
		// bei allen anderen durchlaeufen
		else {
			__C = _C;
			_C = c;
		}
		// im ersten durchlauf bei escape code
		if( (c = getchar()) == 10 && _C == '@' && __C == -1)
			break;
		// bei anderen durchlaeufen und escape code
		else if( c == 10 && _C == '@' && __C == 10 )
			break;
		// nicht im ersten durchlauf
		else if(!firstrun)
			fputc(_C, f);
		// beende ersten durchlauf
		firstrun = 0;
	}
	
	while(1) {
		// datei anzeigen?
		printf("\nDatei anzeigen? (j|n) ");
		scanf("%c", &c);
		printf("\n");
		// wenn ja
		if(c=='j') {
			// mit lesezugriff neu oeffnen
			freopen(path, "r", f);
			// bis End Of File
			while( (c=fgetc(f)) != EOF )
				printf("%c",c);
			// Furt He
			break;
		}
		// wenn nicht
		else if(c=='n')
			// Furt He
			break;
	}
	// Schlussmeldung
	printf("\nExit...");
	
	return 0;
}
