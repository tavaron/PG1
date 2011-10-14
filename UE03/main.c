//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		13.10.2011 v1.0
//      geaendert:	13.10.2011
//      
//      Beschreibung: gibt eine zahlenpyramide aus
//      
//      Eingabe: keine
//      
//      Ausgabe: zahlenpyramide
//      
//      ------------------------------------------------------------------------


#include <stdio.h>

void spaces(int count);
void numbers(int count);

int main(int argc, char** argv)
{
	int i = 0,
		zeilen = 9;
	for(i=zeilen;i>=0;i--)
	{
		spaces(zeilen-i+10);
		numbers(i);
		printf("\n");
	}
	
	for(i=0;i<=zeilen;i++)
	{
		spaces(zeilen-i+10);
		numbers(i);
		printf("\n");
	}
	return 0;
}

void spaces(int count)
{
	int i = 0;
	for(i=0;i<count;i++)
		printf(" ");
}

void numbers(int count)
{
	int i = 0;
	for(i=count;i>=0;i--)
		printf("%d",i);
	for(i=1;i<=count;i++)
		printf("%d",i);
}
