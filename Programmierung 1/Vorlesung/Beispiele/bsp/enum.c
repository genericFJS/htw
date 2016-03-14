#include <stdio.h>
#include <stdlib.h>

enum tWoTa{
	Montag=1, // bei Montag=1, fängt's bei 1 an zu zählen (anstatt 0)
	Dienstag, 
	Mittwoch, 
	Donnerstag,
	Freitag,
	Samstag=Freitag+1+0x10,	// verändert das Wochenende
	Sonntag};
	
enum tWoTa w=1;
	
int main(){
	printf("%d %x \n",Montag, Montag);	// gibt standarmäßig 0 aus; Sonntag wäre 6 usw.
	printf("%d %x \n",Dienstag, Dienstag);
	printf("%d %x \n",Mittwoch, Mittwoch);
	printf("%d %x \n",Donnerstag, Donnerstag);
	printf("%d %x \n",Freitag, Freitag);
	printf("%d %x \n",Samstag, Samstag);
	printf("%d %x \n",Sonntag, Sonntag);
	w=99;	
	printf("%d %x \n",w, w);
	return 0;
}