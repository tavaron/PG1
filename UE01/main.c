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
 *      Beschreibung:   !!!
 *      
 *      Eingabe:    !!!
 * 
 *      Ausgabe:    !!!
 *      
 *      ------------------------------------------------------------------------
 */

#include <stdio.h>

int main(int argc, char** argv)
{
    int zahl = 0;
    printf("Hello world!\n");
    printf("Bitte geben Sie eine Zahl ein: ");
    scanf("%d", &zahl);
    printf("Gleitkomma:    %.2F\nLinksbuendig:  %-d\nRechtsbuendig: %5d", (float) zahl, zahl, zahl);
    return 0;
}
