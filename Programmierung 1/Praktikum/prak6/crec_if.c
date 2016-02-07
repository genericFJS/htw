#include <stdio.h>
#include <stdlib.h>

char vBuf[128];

main(int argc, char* argv[]){
	
	while (1){
		fgets (vBuf, 128, stdin);
		if (strncmp(vBuf,"qq",2)){
			char myChar = vBuf[0];
			if (myChar <= 32 || myChar > 127){
				printf("%c (Dec: %d, Hex: 0x%X) ist kein lesbares ASCII-Zeichen.\n",myChar,myChar,myChar);
			} else if(myChar >= 48 && myChar <= 57){
				printf("%c ist eine Zahl.\n", myChar);
			} else if(myChar >= 65 && myChar <= 90){				
				printf("%c ist ein Großbuchstabe.\n", myChar);
			} else if(myChar >= 97 && myChar <= 122){				
				printf("%c ist ein Kleinbuchstabe.\n", myChar);
			}	else {
				printf("%c ist ein Sonderzeichen.\n", myChar);
			}
		} else {
			break;
		}
	}
	puts("=======");
	puts("Fertig!");
	
}