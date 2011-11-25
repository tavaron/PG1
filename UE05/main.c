//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		17.10.2011 v0.1
//      geaendert:	17.10.2011
//      
//      Beschreibung: 	liest eine zeichenfolge ein und trennt die ersten
//						10 zeichen ab und gibt beide strings getrennt aus.
//						die anzahl der zeichen, ziffern und grossbuchstaben
//						wird gezaehlt.
//      
//      Eingabe:	zeichenfolge
//      
//      Ausgabe: 	zeichenfolgen der ersten 10 zeichen und des rests.
//					anzahl der zeichen, ziffern und grossbuchstaben.
//      
//      ------------------------------------------------------------------------


#include  <stdio.h>


// prototypen
void printEingabe(int length, char eingabe[]);
int getDigitCount(int length, char* eingabe);
int getBigLetterCount(int length, char* eingabe);

int main(int argc, char** argv)
{
	// max zeichenanzahl = 100
	char eingabe[100];
	int i = 0;
	int length = 0;
	
	// bis break
	while(1)
	{
		// eingabeaufforderung
		printf("Bitte Zeichenfolge eingeben: ");
		// von null bis zeichenanzahl
		for(i=0;i<100;i++)
		{
			// wenn char == CR
			if((eingabe[i] = getchar()) == 10)
			{
				// terminiere string
				eingabe[i] = '\0';
				length = i;
				break;
			}
		}
		// beende wenn @
		if(eingabe[0]=='@')
		{
			printf("Exiting...");
			break;
		}
		
		printEingabe(length, eingabe);
	}
	return 0;
}

void printEingabe(int length, char* eingabe)
{
	int i = 0;
	char string10[10], stringRest[90];
	// wenn mehr als 10 zeichen eingegeben
	if(length>10)
	{
		// zeichen 0 bis 9 in ersten string schieben
		for(;i<10;i++)
			string10[i] = eingabe[i];
		// rest verschieben
		for(i=10;i<length;i++)
			stringRest[i-10] = eingabe[i];
		// string terminieren (wegen wiederholten durchlaeufen)
		stringRest[length-10] = '\0';
		// ausgabe
		printf("Der gespeicherte String ist %s\n", string10);
		printf("Die Zeichenfolge enthält %d Zeichen\n", length);
		printf("Die folgenden Zeichen wurden abgeschnitten: %s\n", stringRest);
	}
	else
	{
		// eingegebene zeichen in ersten string kopieren
		for(;i<length;i++)
			string10[i] = eingabe[i];
		// string terminieren  (wegen wiederholten durchlaeufen)
		string10[length] = '\0';
		stringRest[0] = '\0';
		// ausgabe
		printf("Der gespeicherte String ist %s\n", string10);
		printf("Die Zeichenfolge enthält %d Zeichen\n", length);
		printf("Es wurden keine Zeichen abgeschnitten\n");
	}
	printf("Die Zeichenfolge enthaelt %d Ziffern und %d Grossbuchstaben\n\n", getDigitCount(length, eingabe) ,getBigLetterCount(length, eingabe));
}


int getDigitCount(int length, char* eingabe)
{
	int count = 0;
	int i = 0;
	// fuer jedes zeichen
	for(;i<length;i++)
	{
		// wenn es eine zahl ist erhoehe counter
		if(eingabe[i]>=48&&eingabe[i]<=57)
			count++;
	}
	return count;
}

int getBigLetterCount(int length, char* eingabe)
{
	int count = 0;
	int i = 0;
	// fuer jedes zeichen
	for(;i<length;i++)
	{
		// wenn es ein grossbuchsstabe ist erhoehe counter
		if(eingabe[i]>=65&&eingabe[i]<=90)
			count++;
	}
	return count;
}
