#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

long inc = 1;

void ctrl_c_handler (int c)
{
  inc = ( (inc==1) ? -1 : 1);
  return;
}

int main(void)
{
  long count;
  sig_t ret;

  ret = signal(SIGINT, (sig_t) &ctrl_c_handler);
  if (ret == SIG_ERR) {
    perror("signal");
    exit(EXIT_FAILURE);
  }
 
  /* output count continuously */
  for (count=0; ; count+=inc) {
    printf("%08li\n", count);
  }   
  exit(EXIT_SUCCESS);
}
