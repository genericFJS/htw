#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  pid_t ret;

  ret = fork();
  if (ret == -1) {
    printf("fork() failed. Stop.\n");
    exit(EXIT_FAILURE);
  }
  if (ret == 0) { /* Sohn */
    printf("Ich bin der Sohn!\n");
    exit(EXIT_SUCCESS);
  }
  else { /* Vater */
    printf("Ich bin der Vater!\n");
    printf("Der PID des Sohnes betraegt %d.\n", ret);
    exit(EXIT_SUCCESS);
  }
}
