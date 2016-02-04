#include <unistd.h>

int main(void)
{
  fork();
  fork();
  fork();
  sleep(60);

  return 0;
}
