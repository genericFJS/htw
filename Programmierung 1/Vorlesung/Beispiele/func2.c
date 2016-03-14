
#include <stdio.h>



long fakult1(int x); // Funktionsdeklaration
long fakult2(int x);
char vbuf[128]; // Variable ausserhalb von Funktionen
		// globale oder externe Variable
int main()
{
  int x;	// lokale Variable
  long y;
  printf("Berechnung der Fakultaet:\n");
  printf("Eingabe von x:");
  x=atoi(fgets(vbuf,128,stdin));
  printf("Fakultaet von %d: %ld\n",x,fakult1(x));
  y=fakult2(x);
  printf("Fakultaet von %d: %ld\n",x,y);
}
// Funktionsdefinition
long fakult1(int x)
{
  int i;
  long erg=1;
  for (i=1;i<=x;i++)erg*=i;
  return erg;
}

long fakult2(int x) //x ist eine Kopie
{
  long erg=1;
  while (x) erg*=x--;
  printf("Inhalt von vbuf: %s\n",vbuf);
  return erg;
}