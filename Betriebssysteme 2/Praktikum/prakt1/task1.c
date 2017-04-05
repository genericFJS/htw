#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

main(){
	// initialize file
	FILE *f = fopen("zahl.dat", "w");
	fprintf(f, "0");
	fclose(f);
	// create children
	pid_t pid = getppid();
	int forks = 5;
	for (forks; forks>0; forks--){
		if(pid!=0){
			pid = fork();
		}
	}
	if(pid!=0){
		// wait for children
		wait(NULL);
		wait(NULL);
		wait(NULL);
		wait(NULL);
		wait(NULL);
	} else {
		// write to file
		int j= 0;
		while (j<200){
			FILE *fs = fopen("zahl.dat","r+");
			int i;
			fscanf(fs,"%d",&i);
			rewind(fs);
			fprintf(fs,"%d",++i);
			fclose(fs);
			j++;
		}
		// print number
		FILE *fo = fopen("zahl.dat", "r");
		int k;
		fscanf(fo,"%d",&k);
		printf("%d\n",k);
		exit(0);
	}
}