#include "figuren.h"
#include <math.h>
/* a: Seitenlaenge */
double Quadrat(double a)
{
  return a*a;
}

/* a,b: Seitenlaengen */
double Rechteck(double a, double b)
{
  return a*b;
}

/* c: Laenge der Gundlinie,
   a: parallel zu c,
   h: Hoehe (Abstand zw. a und c)*/  
double Trapez(double a, double c, double h)
{
  return (a+c)/2*h;
}

/* a: Laenge Seitenlinie
   h: Hoehe bezueglich a*/
double Parallelogr(double a,double h)
{
  return a*h;
}

/* n: Anzahl der Ecken
   r: Radius (Abstand Mittelpunkt-Ecke)*/
double regVieleck(int n,double r)
{
  return n*r*r*sin(2*3.1415625/n)/2;
}

double Kreis(double r)
{
  return 3.1415625*r*r;
}

double Dreieck(double c, double h)
{
  return c*h/2;
}


