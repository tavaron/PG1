//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		13.10.2011 v0.1
//      geaendert:	13.10.2011
//      
//      Beschreibung: !!!
//      
//      Eingabe: !!!
//      
//      Ausgabe: !!!
//      
//      ------------------------------------------------------------------------


#include <stdio.h>

void spaces(int count);
void numbers(int count);

int main(int argc, char** argv)
{
	int i = 0;
	for(i=0;i<=9;i++)
	{
		spaces(9-i);
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
