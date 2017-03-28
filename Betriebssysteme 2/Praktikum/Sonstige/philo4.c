/* Loesung des Philosophenproblems nach Tanenbaum */
#define N 5
#define RIGHT(i) (((i)+1) % N)
#define LEFT(i) (((i)==N) ? 0: (i)+1)

enum phil_state {THINKING, HUNGRY, EATING};
enum phil_state state[N];     /* geeignet initialisiert */

semaphore mutex = 1;  
semaphore s[N];               /* müssen geschlossen initialisiert werden */

void test(int i)
{
  if ((state[i] == HUNGRY) &&
      (state[LEFT(i)] != EATING) &&
      (state[RIGHT(i)] != EATING)) {
    state[i] = EATING;
    V(s[i]);
  }
}

void get_forks(int i)
{
  P(mutex);
  state[i] = HUNGRY;
  test(i);
  V(mutex);
  P(s[i]);                /* hungrig blockieren oder verlassen, d.h., essen */
}

void put_forks(int i)
{
  P(mutex);
  state[i] = THINKING;
  test(LEFT(i));          /* linken Nachbarn ggf. wecken */
  test(RIGHT(i));         /* rechten Nachbarn ggf. wecken */
}

void philosopher(int n)
{
  while(1) {
    /* denken */
    get_forks(n);
    /* essen */
    put_forks(n); 
  }
}
