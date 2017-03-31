#include <stdio.h>

int main(int argc, char *argv[])
{
  char buffer[512];
  if (argc > 1) {
    strcpy(buffer, argv[1]);
  }
  return 0;
}
