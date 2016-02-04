#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) 
{
  sleep(20);
  fork();          /* 1. */
  sleep(20);
  fork();          /* 2. */
  wait(NULL);
  sleep(20);
  fork();          /* 3. */
  sleep(20);
  return 0;
}
