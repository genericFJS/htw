/* Code für den n-ten Philosophen, naive Loesung */
void philosopher(int n)
{
  while(1) {
    /* denken */
    take_fork(n);             /* rechte Gabel nehmen */
    take_fork((n+1)%5);       /* linke Gabel nehmen */
    /* essen */
    put_fork((n+1)%5);        /* linke Gabel weglegen */
    put_fork(n);              /* rechte Gabel weglegen */
  }
}
