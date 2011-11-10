//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		17.10.2011 v0.1
//      geaendert:	17.10.2011
//      
//      Beschreibung: Liest eine Hex-Zahl ein und gibt diese als Dezimalzahl aus.
//      
//      Eingabe: Hex-Zahl, @ beendet Programm
//      
//      Ausgabe: Dezimalzahl, Eingabeaufforderung
//      
//      ------------------------------------------------------------------------


#include <stdio.h>

int convert(char eingabe[], int length);

int main(int argc, char** argv)
{
	char eingabe[20];
	int i = 0;
	int status = 0;
	// solange status nicht exit
	while(status <= 2)
	{
		i = 0;
		status = 0;
		//eigabeaufforderung
		printf("Bitte geben Sie einen Hexwert ein: ");
		while( (eingabe[i] = getchar()) != 10)
		{
			// wenn CR - break
			if(eingabe[i] == 10)
			{
				status = 1;
				break;
			}
			// wenn akzeptable eingabe
			else if(eingabe[i] >=97 && eingabe[i] <= 102)
				// konvertiere in grossbuchstabe
				eingabe[i] -= 32;
			// tue nichts
			else if(eingabe[i] >= 65 && eingabe[i] <= 70)
				;
			else if(eingabe[i] >= 48 && eingabe[i] <= 57)
				;
			// beende prog
			else if(eingabe[i] == '@')
			{
				printf("Exit...");
				status = 3;
				break;
			}
			// fehlermeldung
			else
			{
				printf("%c is not an hex value!\n\n", eingabe[i]);
				status = 2;
			}
			i++;
		}
		// wenn richtige eingabe dann ausgabe
		if(status <= 1)
			printf("Die eingegebene Zahl hat den Dezimalwert: %d\n\n", convert(eingabe, i));
	}
	return 0;
}

int convert(char* eingabe, int length)
{
	int dezimal = 0;
	int i = 0;
	
	for(i = 0; i<= length; i++)
	{
		// wenn A bis F
		if(eingabe[i] >= 65 && eingabe[i] <= 70)
		{
			// verschiebe um eine stelle
			dezimal *= 16;
			// wandle in int um
			dezimal += eingabe[i] - 55;
		}
		// wenn ziffer
		else if(eingabe[i] >= 48 && eingabe[i] <= 57)
		{
			// verschiebe um eine stelle
			dezimal *= 16;
			// wandle in int um
			dezimal += eingabe[i] - 48;
		}
	}
	
	return dezimal;
}
