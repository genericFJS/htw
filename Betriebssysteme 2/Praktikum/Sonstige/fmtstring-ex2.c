#include <stdio.h>
int main(void)
{
  unsigned char canary[5];
  unsigned char foo[4];
  memset(foo, '\x00', sizeof(foo));
  /* 0 before */ strcpy(canary, "AAAA");
  printf("canary: %02x%02x%02x%02x\n", canary[0], canary[1], 
	 canary[2], canary[3]);
  /* 1 */ printf("%16u%n", 7350, (int*) &foo[0]);
  /* 2 */ printf("%32u%n", 7350, (int*) &foo[1]);
  /* 3 */ printf("%64u%n", 7350, (int*) &foo[2]);
  /* 4 */ printf("%128u%n", 7350, (int*) &foo[3]);
  /* 5 after */ printf("%02x%02x%02x%02x\n", foo[0], foo[1], 
		       foo[2], foo[3]);
  printf("canary: %02x%02x%02x%02x\n", canary[0], canary[1], 
	 canary[2], canary[3]);
  return 0;
}
