#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void cntl_c_handler (int c)
{
  sig_t ret;

  printf("Cntl-C gedrueckt. Toll. Versuchs doch nochmal!\n");

  if ((ret= signal(SIGINT, (sig_t) SIG_IGN)) == SIG_ERR) {
    perror("signal");
  }
  return;
}

int main(int argc, char* argv[])
{
  sig_t ret;

  if ((ret = signal(SIGINT, (sig_t) &cntl_c_handler)) == SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }
  while(1);
  return 0;
}
