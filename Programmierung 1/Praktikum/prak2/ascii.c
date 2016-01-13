#include <stdio.h>
#include <ctype.h>

void main(){
int i, j;
for (i=0; i<4; i++)
	printf("| dec hex Char ");
printf("|\n");
for (i=0; i<128/4; i++){
	printf("\n| ");
	for (j=i; j<128; j+=128/4){
		printf("%3d %2X ", j, j);
		if(isgraph(j))
			printf("  %c  |  ", j);
		else
			printf("  .  |  ");
	}
}
printf("\n");
}
