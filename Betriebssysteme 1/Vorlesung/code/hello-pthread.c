/*
 * Hello, world using pthreads
 * - link with -lpthread
 *
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXITER 200000

void *thread_f(void *arg)
{
  printf("world!\n");
  pthread_exit(NULL);
} 

int main(void)
{
  pthread_t a;
  int ret;

  printf("Hello, ");
  ret = pthread_create(
    &a,    /* pointer to variable containing thread ID */ 
    NULL,              /* pointer to thread attributes */
    (void*) &thread_f,              /* thread function */
    NULL);                      /* pointer to argument */ 
  if (ret != 0) {
    perror("creating 1st thread");
    exit(EXIT_FAILURE);
  }
  pthread_join(a, NULL);
  exit(EXIT_SUCCESS);
}
