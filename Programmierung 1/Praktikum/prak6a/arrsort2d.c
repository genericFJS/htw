#include <stdio.h>
#include <stdlib.h>
#define N 10

char data[][N] = {"Max", "Moritz", "Bolte", "Boeck", \
	"Lempel", "Maecke", "Huckebein", "Schlich", "Helene", "Antonius"};

void printArr(char arr[][N]){
	int i,j;
	for(i = 0; i <  sizeof(data)/N; i++) {
    for(j = 0; j < N; j++) {
        printf("%c", arr[i][j]);
    }
    printf("\n");
	}
}

main(){		
	printf("\x1b[32m");
	int rowA, rowB, x;
	for (rowA = 0; rowA<(N-1); rowA++){
		for (rowB = rowA+1; rowB<N; rowB++){
			x = 0;
			for (x=0; data[rowA][x] == data[rowB][x] && data[rowA][x]!=0; x++){
				;			
			}
			if (data[rowA][x] > data[rowB][x]){
				char tmp;
				for ( ; x<N; x++){
					tmp = data[rowA][x];
					data[rowA][x] = data[rowB][x];
					data[rowB][x] = tmp;
				}
			}
		}
	}
	
	printArr(data);
	
	printf("\x1b[0m");
}