/*
   sigchld.c
 
   demonstrates
   - multiple entry into one and the same handler
   - storing data across multiple handler invocations
   - communication between handler and program via global variable
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define CHILDREN 5

int end = 0;

void catch_sigchld(int);

void catch_sigchld(int signum)
{
  static int cnt=0;
  int status;
  pid_t ret;

  printf("Handler: %ith invocation\n", ++cnt);
  /* does not block, because at least one child is zombie */
  ret = wait(&status);
  printf("child exited, return code %i\n", WEXITSTATUS(status));
  if (cnt == CHILDREN) {
    end = 1;
  }
  return;
}

int main(int argc, char* argv[])
{
  pid_t pid;
  int c;

  if ((signal(SIGCHLD, catch_sigchld)) < 0) {
    perror("signal");
    exit(EXIT_FAILURE);
  }

  for (c=0; c<CHILDREN; c++) {
    if ((pid = fork()) == -1) {
      perror("fork()");
      exit(EXIT_FAILURE);
    }
      if (pid==0) {
	/* Child Code */
	printf("Child No. %d\n", c);
	return 10*c+2;
      }
  }
  /* Father */
  while(!end); 
  printf("Father ends.\n");
  exit(EXIT_SUCCESS);
}

