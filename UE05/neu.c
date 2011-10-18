//      ------------------------------------------------------------------------
//      
//      Datei: neu.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		18.10.2011 v0.1
//      geaendert:	18.10.2011
//      
//      Beschreibung: !!!
//      
//      Eingabe: !!!
//      
//      Ausgabe: !!!
//      
//      ------------------------------------------------------------------------


#include <stdio.h>
#define stringLength 10

int checkLength(char* string);
int getBigLetterCount(char* string);
int getSmallLetterCount(char* string);
int getDigitCount(char* string);

int main(int argc, char** argv)
{
	char mainString[stringLength];
	char subString[100];
	
	printf("Bitte Zeichenkette eingeben: ");
	scanf("%10s", mainString);
	if(checkLength(mainString)==stringLength) scanf("%s", subString);
	
	printf("MainString: %s\n", mainString);
	printf("Anzahl Zeichen MainString: %d\n", checkLength(mainString));
	if(checkLength(mainString)==stringLength) printf("SubString: %s\n", subString);
	else printf("No SubString!\n");
	if(checkLength(mainString)==stringLength) printf("Die Zeichenfolge enthaelt %d Ziffern, %d Grossbuchstaben und %d Kleinbuchstaben.\n", getDigitCount(mainString)+getDigitCount(subString), getBigLetterCount(mainString)+getBigLetterCount(subString), getSmallLetterCount(mainString)+getSmallLetterCount(subString)); 
	else printf("Die Zeichenfolge enthaelt %d Ziffern, %d Grossbuchstaben und %d Kleinbuchstaben.\n", getDigitCount(mainString), getBigLetterCount(mainString), getSmallLetterCount(mainString));
	if(checkLength(mainString)==stringLength) printf("Die Zeichenfolge ist %d Zeichen lang", checkLength(mainString)+checkLength(subString));
	else printf("Die Zeichenfolge ist %d Zeichen lang", checkLength(mainString));
	return 0;
}

int checkLength(char* string)
{
	int length = 0;
	while(1)
	{
		if(string[length] == 10 || string[length] == '\0')
			break;
		else
			length++;
	}
	return length;
}

int getBigLetterCount(char* string)
{
	int i = checkLength(string)-1;
	int counter = 0;
	for(;i>=0;i--)
		if(string[i] >= 65 && string[i] <= 90)
			counter++;
	return counter;
}

int getSmallLetterCount(char* string)
{
	int i = checkLength(string)-1;
	int counter = 0;
	for(;i>=0;i--)
		if(string[i] >= 97 && string[i] <= 122)
			counter++;
	return counter;
}

int getDigitCount(char* string)
{
	int i = checkLength(string)-1;
	int counter = 0;
	for(;i>=0;i--)
		if(string[i] >= 48 && string[i] <= 57)
			counter++;
	return counter;
}
