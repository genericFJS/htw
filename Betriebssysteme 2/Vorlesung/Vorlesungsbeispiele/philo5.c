/* alternative Loesung des Philosophenproblems */
#define N 5
#define RIGHT(i) (((i)+1) % N)
#define LEFT(i) (((i)==N) ? 0: (i)+1)

semaphore free = N-1;                    /* nicht-binaerer Semaphor */  
semaphore fork[N] = { 1, 1, 1, 1, 1};    /* offen initialisiert */

void philosopher(int n)
{
  while(1) {
    /* denken */
    P(free);
    P(fork[RIGHT(n)]);
    P(fork[LEFT(n)]);
    /* essen */
    V(fork[LEFT(n)]);
    V(fork[RIGHT(n)]);
    V(free);
  }
}
