#include <stdlib.h>

int main(int argc, char* argv[])
{
  if (argc==2) {
    exit (atoi(argv[1]));
  }
  else {
    exit(42);
  }
}
