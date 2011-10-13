/*
 *      ------------------------------------------------------------------------
 *      
 *      Datei:      UE02/main.c
 *      
 *      Name:       Marius Christ
 *      Matr.-Nr.:  954402
 *      Datum:      10.10.2011 v1.0
 *      geaendert:  10.10.2011
 *      
 *      Beschreibung:   Das Programm gibt eine Tabelle mit den Fahrenheitwerten
 * 						0 bis 200 in 20er-Schritten und die dazu passenden
 * 						Celciuswerte aus.
 *      
 *      Eingabe:    keine
 *      
 *      Ausgabe:    Temperaturtabelle
 *      
 *      ------------------------------------------------------------------------
 */

#include <stdio.h>

int main(int argc, char** argv)
{
    double 	tc = 0, //Temperatur in Celcius
			tf = 0; //Temperatur in Fahrenheit
	printf("Fahrenheit   Celcius\n"); //Gebe Kopfzeile aus
	for(tf=0;tf<=200;) //Solange tf <= 200 ist...
	{
		tc = 5.0 / 9.0 * ( tf - 32.0 ); //Rechne passenden Celciuswert aus
		printf("%10.1lf%10.1lf\n", tf, tc); //Gebe Werte aus
		tf=tf+20.0; //Addiere 20 Grad Fahrenheit
	}

    return 0; //Beende ohne Fehler
}
