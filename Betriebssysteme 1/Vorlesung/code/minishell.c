#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 80

int main(void) 
{
  pid_t ret;
  char buf[MAXLINE], *pt;
  int quit = 0;

  while( quit != 1 ) {
    /* print the prompt */
    printf("->"); 
    /* read in a new command to be executed */
    pt = fgets(buf, MAXLINE, stdin);
    if (pt == NULL) {
      perror("fgets");
      exit(EXIT_FAILURE);
    }
    buf[strlen(buf)-1] = 0;

    if (!strcmp(buf, "quit\n")) {
      /* quit the shell */
      quit = 1;
      continue; 
    }
    if( (ret = fork()) == -1) {
      perror("fork");
      exit(EXIT_FAILURE);  
    }
    if (ret == 0) {        
      /* Son executes the input command */
      execlp(buf, buf, NULL);           
      printf("could not execute: %s\n", buf);
      exit(EXIT_FAILURE);
    }
    
    if ((ret=waitpid(ret, NULL, 0)) < 0) {                    /* Vater */
      printf("waitpid failed\n");
      exit(EXIT_FAILURE);
    }
  }
  exit (EXIT_SUCCESS);
}      
