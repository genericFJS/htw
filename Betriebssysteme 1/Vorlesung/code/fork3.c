#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int var = 42;

int main(int argc, char* argv[])
{
  pid_t ret;
  if ((ret = fork())== -1) {
    printf("fork() failed. Stop.\n");
    exit(EXIT_FAILURE);
  }
  if (ret == 0) { /* Sohn */
    var = 32168;
    printf("Sohns 'var' hat den Wert %d.\n", var);
    sleep(5);
    printf("Sohns 'var' hat (immer noch) den Wert %d.\n", var);
    exit(EXIT_SUCCESS);
  }
  else { /* Vater */
    sleep(2);
    printf("Vaters 'var' hat den Wert %d.\n", var);
    exit(EXIT_SUCCESS);
  }
}
