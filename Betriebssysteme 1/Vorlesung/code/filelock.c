/*
    example for blocking file locking
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OURFILE "./mytmpfile"

int main(int argc, char* argv[])
{
  int fd, ret;
  char buf_son[] = "Son writes something\n";
  char buf_father[] = "Father writes something\n";

  /* OURFILE is opened for appending writes and is created if necessary */
  if ((fd = open(OURFILE, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR)) == -1){
    perror("open()");
    exit(EXIT_FAILURE);
  }

  if ((ret = fork()) == -1) {
    perror("fork()");
    close(fd);
    exit(EXIT_FAILURE);
  }

  if (ret == 0) {                                       /* Son */
    /* obtain the lock */
    printf("Son tries to get lock\n");
    if ((ret = lockf(fd, F_LOCK, 0)) == -1) {
      perror("lockf()");
      exit(EXIT_FAILURE);
    }
    printf("Son got lock\n");

    /* use the resource */
    ret = write(fd, buf_son, sizeof(buf_son)-1);
    printf("Son wrote %d bytes into file.\n", ret);

    /* return lock */
    printf("Son returns lock\n");
    if ((ret = lockf(fd, F_ULOCK, 0)) == -1) {
      perror("u-lockf()");
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);                            /* Son ends */
  }
  else {                                             /* Father */
    //    sleep(5);

    /* obtain the lock */
    printf("Father tries to get lock\n");
    if ((ret = lockf(fd, F_LOCK, 0)) == -1) {
      perror("lockf()");
      close(fd);
      exit(EXIT_FAILURE);
    }
    printf("Father got lock\n");

    /* use the resource */
    ret = write(fd, buf_father, sizeof(buf_father)-1);
    printf("Father wrote %d bytes into file.\n", ret);

    /* return lock */
    printf("Father returns lock\n");
    if ((ret = lockf(fd, F_ULOCK, 0)) == -1) {
      perror("u-lockf()");
      close(fd);
      exit(EXIT_FAILURE);
    }

    /* unlock file again */
    if ((ret = lockf(fd, F_ULOCK, 0)) == -1) {
      perror("unlocking lockf");
      close(fd);
      exit(EXIT_FAILURE);
    }
  }
  
  /* epilogue, executed by father only */
  close(fd);
  wait(NULL); 
  exit(EXIT_SUCCESS);
}
