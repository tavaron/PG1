/*
 *      ------------------------------------------------------------------------
 *      
 *      Datei:      UE01/main.c
 *      
 *      Name:       Marius Christ
 *      Matr.-Nr.:  954402
 *      Datum:      10.10.2011 v0.0
 *      geaendert:  10.10.2011
 *      
 *      Beschreibung:   nimmt einen integer entgegen und gibt diesen formatiert aus
 *      
 *      Eingabe:    integer
 * 
 *      Ausgabe:    formatierter integer
 *      
 *      ------------------------------------------------------------------------
 */

#include <stdio.h>


int main(int argc, char** argv)
{
    int zahl = -1;
    printf("Hello World\n");
    while(zahl!=0)
    {
		zahl = -1;
		printf("Bitte geben Sie eine Zahl ein: ");
		scanf("%d", &zahl);
		while(getchar()!=10);
		if(zahl!=0)
			printf("Gleitkomma:    %.2F\nLinksbuendig:  %-d\nRechtsbuendig: %5d\n", (float) zahl, zahl, zahl);
	}
    return 0;
}
