//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		01.11.2011 v0.1
//      geaendert:	01.11.2011
//      
//      Beschreibung: wandelt eine gleitpunktpunktzahl
//      
//      Eingabe: eine gleitpunktzahl als string
//      
//      Ausgabe: eine gleitpunktzahl als double
//      
//      ------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>

int isDouble(char* string);

int main(int argc, char** argv)
{
	// bis break
	while(1)
	{
		char eingabe[20];
		double ausgabe;
		// eingabeaufforderung
		printf("Bitte geben Sie eine Gleitkommazahl ein: ");
		scanf("%s", eingabe);
		
		// Furt He
		if(eingabe[0]=='@')
		{
			printf("Exit...");
			break;
		}
		// pruefe ob zeichenfolge passend ist	
		if(isDouble(eingabe))
		{
			ausgabe = atof(eingabe);
			printf("%.2lf wurde eingegeben.\n\n", ausgabe);
		}
		else
			printf("Eingabefehler!\n\n");
			
	}
	return 0;
}

int isDouble(char* eingabe)
{
	int bool = 0;
	int wrong = 0;
	int dots = 0;
	int i = 1;
	
	// wenn erstes zeichen == vorzeichen || ziffer
	if(eingabe[0]=='+'||eingabe[0]=='-'||(eingabe[0]>=48&&eingabe[0]<=57))
	{
		// fuer jedes zeichen
		for(;i<20;i++)
		{
			// terminierung
			if(eingabe[i]=='\0')
				break;
			else if(eingabe[i]>=48&&eingabe[i]<=57)
				;
			// punkte zaehlen
			else if(eingabe[i]=='.')
				dots++;
			// falsche weichen zaehlen
			else
				wrong++;
		}
		// wenn 1 oder weniger punke und kein falsches zeichen
		if(dots<=1&&wrong==0)
			// return-value = true
			bool = 1;
	}
	return bool;
}
