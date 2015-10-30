#include <stdio.h>
#include <stdlib.h>

char vBuf[128];

int main(){
   double durchmesser_mm;
   double flaeche;
   double pi = 3.14;

   printf("Berechnung der Kreisfläche \n \n");

   printf("Eingabe des Durchmessers in mm: ");
   fgets(vBuf, 128, stdin);
   durchmesser_mm = atof (vBuf);

   flaeche = pi*durchmesser_mm*durchmesser_mm/400;
   printf("Flächeninhalt in cm²: %.4f \n",flaeche);
}
