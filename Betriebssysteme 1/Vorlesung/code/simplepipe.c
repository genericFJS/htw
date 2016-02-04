/*
  
  - creates a pipe and transmits data via it from son to father
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READIDX 0
#define WRITEIDX 1

char exampletxt[] = "Lieber Sohn,\nalles Gute sendet Dir\nDein lieber Vater\n";

int main(int argc, char* argv[])
{
  int ret, pipefd[2], rcvd, c;
  char buf[80];

  /* Create a Pipe */
  ret = pipe(pipefd);
  if (ret == -1) {    /* pipe() failed */
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  
  /* Create a Son Process */
  ret = fork();
  if (ret == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  /* Son */
  if (ret == 0) { 
    close(pipefd[WRITEIDX]);  /* close write end */
    c = 0;
    do {   /* receive bytes in a loop */
      rcvd = read(pipefd[READIDX], &buf[c], 1);
      if (rcvd == -1) {
	perror("read from pipe");
	exit(EXIT_FAILURE);
      }
      c++;
    } while(rcvd != 0);

    printf("Sohn empfing folgende Nachricht:\n%s", buf);
    close(pipefd[READIDX]);
    exit(EXIT_SUCCESS);
  }

  /* Father */
  else {  
    close(pipefd[READIDX]);
    /* send a single message via pipe */
    write(pipefd[WRITEIDX], exampletxt, strlen(exampletxt)+1);
    close(pipefd[WRITEIDX]);
    exit(EXIT_SUCCESS); 
  }
}
