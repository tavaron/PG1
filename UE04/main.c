//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		17.10.2011 v0.1
//      geaendert:	17.10.2011
//      
//      Beschreibung: !!!
//      
//      Eingabe: !!!
//      
//      Ausgabe: !!!
//      
//      ------------------------------------------------------------------------


#include <stdio.h>

int convert(char eingabe[], int length);

int main(int argc, char** argv)
{
	char eingabe[20];
	int i = 0;
	int status = 0;
	
	while(status <= 2)
	{
		i = 0;
		status = 0;
		printf("Bitte geben Sie einen Hexwert ein: ");
		while( (eingabe[i] = getchar()) != 10)
		{
			
			if(eingabe[i] == 10)
			{
				status = 1;
				break;
			}
			else if(eingabe[i] >=97 && eingabe[i] <= 102)
				eingabe[i] -= 32;
			else if(eingabe[i] >= 65 && eingabe[i] <= 70)
				;
			else if(eingabe[i] >= 48 && eingabe[i] <= 57)
				;
			else if(eingabe[i] == 64)
			{
				printf("Exit...");
				status = 3;
				break;
			}
			else
			{
				printf("%c is not an hex value!\n", eingabe[i]);
				status = 2;
			}
			i++;
		}
		if(status <= 1)
			printf("Die eingegebene Zahl hat den Dezimalwert: %d\n", convert(eingabe, i));
	}
	return 0;
}

int convert(char eingabe[], int length)
{
	int dezimal = 0;
	int i = 0;
	
	for(i = 0; i<= length; i++)
	{
		if(eingabe[i] >= 65 && eingabe[i] <= 70)
		{
			dezimal *= 16;
			dezimal += eingabe[i] - 55;
		}
		else if(eingabe[i] >= 48 && eingabe[i] <= 57)
		{
			dezimal *= 16;
			dezimal += eingabe[i] - 48;
		}
	}
	
	return dezimal;
}
