/*
    Example Program - System V Semaphores and Shared Memory Segment
    03/27/2013
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
# include <sys/shm.h>

#define SHM_SIZE 4096

union semun {
  int val;                    /* value for SETVAL */
  struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
  unsigned short int *array;  /* array for GETALL, SETALL */
  struct seminfo *__buf;      /* buffer for IPC_INFO */
};

/* Globals */
int shmid, semid;
char *adrshm;

/*
 * SysCall Error
 */
void sce(char *msg)
{
  perror(msg);
  exit(EXIT_FAILURE);
}

/*
   Simple Semaphore API: P(), V(), Init()
*/
void P(int semid, int index)
{
  int ret;
  struct sembuf op;

  op.sem_num = index;
  op.sem_op = -1;
  op.sem_flg = 0;
  if ((ret = semop(semid, &op, 1)) == -1) {
    sce("semop(), P()");
  }
}

void V(int semid, int index)
{
  int ret;
  struct sembuf op;

  op.sem_num = index;
  op.sem_op = +1;
  op.sem_flg = 0;
  if ((ret = semop(semid, &op, 1)) == -1) {
    sce("semop(), V()");
  }
}

void Init(int semid, int index, int value)
{
  int ret;
  union semun arg;

  arg.val = 1;
  if ((ret = semctl(semid, index, SETVAL, value)) == -1) {
    sce("semctl(), SETVAL");
  }
}


void producer(void)
{
  time_t current_time;
  
  while(1) {
    current_time = time(NULL);
    P(semid, 0);
    sprintf((char*) adrshm, "%s", ctime(&current_time));
    V(semid, 0);
    sleep(1);
  }
}

void consumer(void)
{
  while(1) {
    P(semid, 0);
    printf("%s", adrshm);
    V(semid, 0);
    sleep(1);
  }
}


int main(void)
{
  int ret;
  pid_t son1, son2;

  /* ESTABLISH IPC FACILITIES */ 

  /* create an unnamed semaphore set (with one semaphore, only) */
  if ((semid = semget(IPC_PRIVATE, 1, IPC_CREAT|0600)) == -1) {
    sce("semget");
  } 
  /* init the semaphore (set) as open */
  Init(semid, 0, 1);

  /* create an unnamed shared memory segment */
  if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT|0600)) == -1) {
    sce("shmget");
  }
  /* attach the segment into virtual address space, let system choose address */
  if ((adrshm = (char*) shmat(shmid, NULL, 0)) == (void*) -1) {
    sce("shmat");
  }

  /* TRANSFER DATA */

  /* create two son processes, consumer and producer */
  if (( son1 = fork()) == -1) {
    sce("1st fork()");
  }
  if (son1 == 0) {
    producer();   /* loops infinitely */
  }

  if (( son2 = fork()) == -1) {
    sce("2nd fork()");
  }
  if (son2 == 0) {
    consumer();   /* loops infinitely */
  }

  /* wait for a specific input */
  while( (ret = getchar()) != 'q')
    ;

  /* CLEAN UP */

  /* kill son processes */
  if ((ret = kill(son1, SIGKILL)) == -1) {
    perror("kill() 1st son");
  }
  if ((ret = kill(son2, SIGKILL)) == -1) {
    perror("kill() 2nd son");
  }
  /* detach and destroy shared memory segment */
  if ((ret = shmdt(adrshm)) == -1) {
    perror("shmdt()");
  }
  if ((ret = shmctl(shmid, IPC_RMID, NULL)) == -1) {
    perror("shmctl(), IPC_RMID");
  }
  /* delete semaphore set */
  if ((ret = semctl(semid, 0, IPC_RMID)) == -1) {
    perror("semctl(), IPC_RMID");
  }

  printf("Father ends.\n");
  exit(EXIT_SUCCESS);
}



