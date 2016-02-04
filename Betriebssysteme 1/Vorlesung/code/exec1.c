#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int ret;

  printf("%s vor Aufruf von execl()\n", argv[0]);
  ret = execl("/bin/ls", "ls", NULL);
  if (ret == -1) {
    printf("execl() ging schief. Und nun?\n");
    exit (EXIT_FAILURE);
  }
  /* wird nicht erreicht ! */
  printf("%s nach Aufruf von execl()\n", argv[0]);
  exit (EXIT_SUCCESS);
}
