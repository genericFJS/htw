#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char vBuf[128];

main(int argc, char* argv[]){
	
	while (1){
		fgets (vBuf, 128, stdin);
		if (strncmp(vBuf,"qq",2)){
			char myChar = vBuf[0];
			if(isdigit(myChar)){
				printf("%c ist eine Zahl.\n", myChar);
			} else if(isupper(myChar)){				
				printf("%c ist ein Großbuchstabe.\n", myChar);
			} else if(islower(myChar)){				
				printf("%c ist ein Kleinbuchstabe.\n", myChar);
			}	else if (ispunct(myChar)){
				printf("%c ist ein Sonderzeichen.\n", myChar);
			} else {
				printf("%c (Dec: %d, Hex: 0x%X) ist kein lesbares ASCII-Zeichen.\n",myChar,myChar,myChar);
			}
		} else {
			break;
		}
	}
	puts("=======");
	puts("Fertig!");
	
}