//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		31.10.2011 v0.1
//      geaendert:	31.10.2011
//      
//      Beschreibung: !!!
//      
//      Eingabe: !!!
//      
//      Ausgabe: !!!
//      
//      ------------------------------------------------------------------------


#include <stdio.h>
#include <math.h>
#define genauigkeit -5

double ownSin(double x);

int main(int argc, char** argv)
{
	double deg, rad;
	int status = -1;
	char c;
	while(status<0)
	{
		printf("Bitte geben Sie einen Winkel in Grad ein: ");
		deg = 0;
		scanf("%lf",&deg);
		while((c=getchar()) != 10) if(c=='@') status=0;
		if(deg == 0)
		{
			printf("Keine Eingabe...\n");
		}
		else
		{
			rad = deg / 180.0 * M_PI;
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
	while(part >= pow(10, genauigkeit)||part <= pow(10, genauigkeit)*-1)
	{
		i = i+2;
		sig = -sig;
		part = part * x*x / i / (i-1);
		sin_x = sin_x + sig * part;
	}
	return sin_x;
}
