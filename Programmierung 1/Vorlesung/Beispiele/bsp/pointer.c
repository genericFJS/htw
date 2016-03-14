#include <stdio.h>
#include <stdlib.h>

int main(){
	int i=99, *pi=&i;
	// &: Adressoperator
	printf("i: %d &i: %p \n", i, &i);
	// folgendes gibt nicht 99, sondern die Adresse von i (und die eigene) aus.
	// erst über *pi wird der Wert des Pointers ausgegeben (-> Dereferenzieren)
	printf("pi: %lx &pi: %p \n *pi: %d\n", pi, &pi, *pi);
	// Äquivalent dazu: (Arrays und Pointer sind in C sehr eng miteinander verwandt)
	printf("pi: %lx &pi: %p \n pi[0]: %d\n", pi, &pi, pi[0]);
	
	return 0;
}