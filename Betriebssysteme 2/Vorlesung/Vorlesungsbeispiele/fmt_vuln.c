#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

int main(int argc, char *argv[]) 
{ 
  char text[1024]; 
  static int test_val = -72; 

  if(argc < 2){ 
    printf("Usage: %s <text to print>\n", argv[0]); 
    exit(0); 
  } 
  strcpy(text, argv[1]); 

  /* The right way to print user-controlled input: */
  printf("The right way:\n"); 
  printf("%s", text); 

  /* The wrong way to print user-controlled input: */
  printf("\nThe wrong way:\n"); 
  printf(text); 

  printf("\n"); 
  /* Debug output */
  printf("[*] test_val @ 0x%08x = %d 0x%08x\n", &test_val, test_val, test_val); 
  return 0; 
}
