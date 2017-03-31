#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

main(){
	int forks = 5;
	pid_t pid;
	pid = fork();
	forks--;
	for (forks; forks>0; forks--){
		if(pid!=0){
			pid = fork();
		}
	}
	if(pid!=0){
		printf("Vater\n");
	} else {
		printf("Sohn\n");
	}
}