#include <stdio.h>
#include <stdlib.h>

char vBuf[128];

main(int argc, char* argv[]){
	
	int active = 1;
	while (active){
		fgets (vBuf, 128, stdin);
		char myChar = vBuf[0];
		switch (vBuf[0]){
			case  48 ... 57:
				printf("%c ist eine Zahl.\n", myChar);
				break;
			case  65 ... 90:
				printf("%c ist ein Großbuchstabe.\n", myChar);
				break;
			case  97 ... 122:				
				if (!strncmp(vBuf,"qq",2)){
					active = 0;
					break;
				}
				printf("%c ist ein Kleinbuchstabe.\n", myChar);
				break;
			case 33 ... 47:
			case 58 ... 64:
			case 91 ... 96:
			case 123 ... 127:
				printf("%c ist ein Sonderzeichen.\n", myChar);
				break;
			default:				
				printf("%c (Dec: %d, Hex: 0x%X) ist kein lesbares ASCII-Zeichen.\n",myChar,myChar,myChar);
				break;
		}
	}
	puts("=======");
	puts("Fertig!");
	
}