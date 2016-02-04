#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) 
{
  pid_t ret;

  ret = fork();
  if (ret == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if (ret == 0) { /* Sohn */
    printf("Sohn geht schlafen...\n");
    sleep(10);
    printf("Sohn erwacht und endet.\n");
    exit(EXIT_SUCCESS);
  }
  else {         /* Vater */
    printf("Vater wartet auf Sohns Ende.\n");
    ret = wait(NULL);
    if (ret == -1) {
      perror("wait");
      exit(EXIT_FAILURE);
    }
    printf("Vater endet (nach Sohn).\n");
    exit(EXIT_SUCCESS);
  }
}
