//Demonstriert local static

#include <stdio.h>

// Funktionsdefinition
long fakult1(int x)
{
  int i;
  static int count;// automatisch mit 0 initialisiert
  count ++;
  long erg=1;
  for (i=1;i<=x;i++)erg*=i;
  printf("Das ist der %d-te Aufruf von fakult1\n",count);
  return erg;
}

char vbuf[128];

int main()
{
  int x;	// lokale Variable
  long y;
  printf("Berechnung der Fakultaet:\n");
  printf("Eingabe von x:");
  x=atoi(fgets(vbuf,128,stdin));
  while (x)
  {
    printf("Fakultaet von %d: %ld\n",x,fakult1(x));
    x--;
  }
  return 0;
}