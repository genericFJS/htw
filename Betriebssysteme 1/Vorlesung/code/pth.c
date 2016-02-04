/*
 * "Hello, world!" with GNU Pth
 * - requires deb packages lib2pth, libpth-dev
 * - do not forget to link with -lpth 
 */
#include <pth.h>
#include <stdio.h>
#include <stdlib.h>

void *pth_thread(void *arg)
{
  printf("world\n");
  pth_exit(NULL);
}

int main(void)
{
  pth_t tid;

  if (!pth_init()) {
    printf("No pth lib available\n");
    exit(EXIT_FAILURE);
  }
  printf("Hello, ");

  tid = pth_spawn(PTH_ATTR_DEFAULT, &pth_thread, NULL);
  if (!tid) {
    printf("Could not spawn thread\n");
    exit(EXIT_FAILURE);
  }

  pth_join(tid, NULL);

  return 0;
}
