//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		31.10.2011 v0.1
//      geaendert:	31.10.2011
//      
//      Beschreibung: berechnet bogenmass und sinus mit eigener/bibliotheksfunktion
//      
//      Eingabe: winkel in grad
//      
//      Ausgabe: sinus des winkels
//      
//      ------------------------------------------------------------------------


#include <stdio.h>
#include <math.h>
// laufzeit bis durchlaufnr^genauigkeit
#define genauigkeit -5

double ownSin(double x);

int main(int argc, char** argv)
{
	double deg, rad;
	int status = -1;
	char c;
	
	while(status<0)
	{
		// eingabeaufforderung
		printf("Bitte geben Sie einen Winkel in Grad ein: ");
		deg = 0;
		// lese gradzahl ein
		scanf("%lf",&deg);
		
		// lese chars vom puffer bis CR
		while((c=getchar()) != 10)
			// wenn @ beende schleife/programm
			if(c=='@') status=0;
		// fehler bei 0 grad / falscher eingabe
		if(deg == 0)
		{
			printf("Keine Eingabe...\n");
		}
		else
		{
			// berechne winkel in bogenmass
			rad = deg / 180.0 * M_PI;
			// gebe ergebnis aus
			printf("Sinus ownSin: %lf\n", ownSin(rad));
			printf("Sinus Math.h: %lf\n\n", sin(rad));
		}
	}
	return status;
}

double ownSin(double x)
{
	int i = 1, sig = 1;
	double sin_x = x, part = x;
	// solange zwischenergebnis groeßer x^genauigkeit
	while(part >= pow(10, genauigkeit)||part <= pow(10, genauigkeit)*-1)
	{
		// addiere zusaetlichen schritt
		i = i+2;
		// wechsele vorzeichen
		sig = -sig;
		// berechne zwischenergebnis
		part = part * x*x / i / (i-1);
		// addiere ergebnis*vorzeichen
		sin_x = sin_x + sig * part;
	}
	return sin_x;
}
