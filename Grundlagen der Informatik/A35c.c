#include<stdio.h>
#include<stdlib.h>

int multA(int fak, int exp){
	if (exp == 0){
		return 1;
	} else if( exp == 2){
		return fak*fak;	
	} else if( exp%2 == 0){
		return sqr(multA(fak, exp/2),2);
	} else {
		return fak*sqr(multA(fak, (exp-1)/2));
	}
}

int sqr(int x){
	return x*x;
}

int main(){
printf("%d\n",multA(2,17));
return 0;
}
