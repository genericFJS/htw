/*
    reads a line from stdin and sends it to message queue INKEY
    receives a similar message from OUTKEY
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <signal.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "share.h"

#define MAXLINE 2048


char pline[MAXLINE], cline[MAXLINE];


int main(int argc, char* argv[])
{
  int iid, oid, ret;

  iid = msgget(INKEY, 0);
  if (iid == -1) {
    perror("client: msgget() input");
    exit(EXIT_FAILURE);
  }
  oid = msgget(OUTKEY, 0);
  if (oid == -1) {
    perror("client: msgget() output");
    exit(EXIT_FAILURE);
  }

  while (fgets(pline, MAXLINE, stdin)) {
    ret = msgsnd(iid, pline, strlen(pline), 0);
    if (ret == -1) {
      printf("client: msgsnd()");
    }
    ret = msgrcv(oid, cline, MAXLINE, 0, 0);
    if (ret == -1) {
      printf("client: msgrcv()");
    }
    else {
      printf("%s", cline);
    }
  }
  exit(EXIT_SUCCESS);
}
