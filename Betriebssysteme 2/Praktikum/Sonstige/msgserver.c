#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <signal.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "share.h"

int end = 0;

void sigint_handler(void *in)
{
  end = 1;
}

void rot13(char *buf)
{
  int idx=0;
  char c;

  c = buf[idx];
  while(c) {
    if (isalpha(c)) 
      buf[idx] = (toupper(c) <= 'M') ? c+13 : c-13;
    c = buf[++idx];
  } 
}

int main(int argc, char* argv[])
{
  int input_id, output_id, ret;
  ssize_t rcvlength;
  char *msgbuf;
  
  msgbuf = malloc(MAXSIZE);
  if (!msgbuf) {
    perror("malloc();");
    exit(EXIT_FAILURE);
  }
  
  ret = (int) signal(SIGINT, (__sighandler_t) sigint_handler);
  if (ret == -1) {
    free(msgbuf);
    perror("signal()");
    exit(EXIT_FAILURE);
  }

  /* Create two Message Queues */
  input_id = msgget(INKEY, IPC_CREAT|0622);
  if (input_id == -1) {
    perror("msgget() input");
    exit(EXIT_FAILURE);
  }
  output_id = msgget(OUTKEY, IPC_CREAT|0644);
  if (output_id == -1) {
    perror("msgget() output");
    exit(EXIT_FAILURE);
  }

  while (end != 1) {
    rcvlength = msgrcv(input_id, msgbuf, MAXSIZE, 0, MSG_NOERROR);
    if (rcvlength == -1) {
      perror("msgrcv()");
      exit(EXIT_FAILURE);
    } 

    rot13(msgbuf);

    ret = msgsnd(output_id, msgbuf, rcvlength, 0);
  }

  ret = msgctl(input_id, IPC_RMID, NULL);
  if (ret == -1) {
    perror("msgctl(), remove, input queue");
  }
  ret = msgctl(output_id, IPC_RMID, NULL);
  if (ret == -1) {
    perror("msgctl, remove, output queue");
  }

  free(msgbuf);
  exit(EXIT_SUCCESS);

}
