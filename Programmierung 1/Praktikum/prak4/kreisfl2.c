#include <stdio.h>
#include <stdlib.h>

char vBuf[128];

int main(){
   int durchmesser_mm;
   int flaeche_vk;
   int flaeche_nk;
   int flaeche;
   int pi = 314;

   printf("Berechnung der Kreisfläche \n \n");

   printf("Eingabe des Durchmessers in mm: ");
   fgets(vBuf, 128, stdin);
   durchmesser_mm = atoi (vBuf);

   flaeche = pi*durchmesser_mm*durchmesser_mm/4;
   flaeche_vk = flaeche/10000;
   //flaeche_nk = flaeche-(flaeche_vk*10000);
   flaeche_nk = flaeche%10000;
   printf("Flächeninhalt in cm²: %d.%04d \n",flaeche_vk,flaeche_nk);
}
