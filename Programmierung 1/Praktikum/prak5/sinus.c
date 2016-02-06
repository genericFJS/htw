#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char vbuf[128];

double sinus(double x){
	double summand = x;
	double xSquare = x*x;
	int fak = 2;
	do{
		printf("Summand: %g\n", summand);
		summand = -1 * summand * xSquare / (fak++ * fak++);
		x += summand;
	} while(fabs(summand)>0.00001);
	return x;
}

int main(){
	printf("Zahl eingeben: ");
	fgets(vbuf, 128, stdin);
	double x = atof(vbuf);
	printf("sinus(%g)=%.4f\n",x,sinus(x));
	printf("sinus(%g)=%.4f\n",x,sin(x));
}