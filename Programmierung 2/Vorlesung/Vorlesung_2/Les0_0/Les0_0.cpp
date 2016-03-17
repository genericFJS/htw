#include <stdio.h>                /* Les0_0 */

void main(){ /* Nachteile von printf, scanf */
	auto x=1.5; 
	printf("x = %d \n",x); /* Fehler: Wert x=0  */
	printf("x = %f \n",x); /* korrektes Format */
	getchar();
}
