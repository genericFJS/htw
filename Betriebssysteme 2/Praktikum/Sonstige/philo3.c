/* Code für den n-ten Philosophen, 1 Semaphor */
semaphore eat = 1;        /* Init: offen */

void philosopher(int n)
{
  while(1) {
    /* denken */
    P(eat);                   /* Erlaubnis zum Aufnehmen der Gabeln einholen */
    take_fork(n);             /* rechte Gabel nehmen */
    take_fork((n+1)%5);       /* linke Gabel nehmen */
    /* essen */
    put_fork((n+1)%5);        /* linke Gabel weglegen */
    put_fork(n);              /* rechte Gabel weglegen */
    V(eat);                   /* Erlaubnis zurückgeben */
  }
}
