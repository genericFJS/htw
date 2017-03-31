/* Code für den n-ten Philosophen, 'vorsichtiges' Greifen nach 2. Gabel */
void philosopher(int n)
{
  while(1) {
    /* denken */
  again:
    take_fork(n);             /* rechte Gabel nehmen */
    if (!available(fork((n+1)%5)) { /* falls linke Gabel nicht verfuegbar ... */
      put_fork(n);            /* ... rechte Gabel zuruecklegen ... */ 
      sleep(10);              /* ... eine Weile warten ... */ 
      goto again;             /* ... und von vorn probieren. */
    }
    take_fork((n+1)%5);       /* linke Gabel nehmen */
    /* essen */
    put_fork((n+1)%5);        /* linke Gabel weglegen */
    put_fork(n);              /* rechte Gabel weglegen */
  }
}
