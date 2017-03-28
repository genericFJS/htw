#include <stdio.h>

int main(void)
{
  char *cmd = "/bin/sh";
  char *args[2];

  args[0] = "robixd";
  args[1] = NULL;
  
  execve(cmd, args, NULL);
}
