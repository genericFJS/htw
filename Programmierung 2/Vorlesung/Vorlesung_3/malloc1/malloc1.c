/* MALLOC1.C: This program allocates memory with
 * malloc, then frees the memory with free.
 */

#include <stdlib.h>         /* For _MAX_PATH definition */
#include <stdio.h>
#include <malloc.h>
#include <string.h>

void main()
{
   char *string;

   printf("_MAX_PATH  = %d\n",_MAX_PATH);

   /* Allocate space for a path name */
   string = (char *)malloc( _MAX_PATH );
   
   if( string == NULL ){
      printf( "Insufficient memory available\n" );
      return;
   }
   else
      printf( "Memory space %d Byte allocated for path name\n",
		       _MAX_PATH);

   if(strlen("C:\\temp\\malloc1.c") < _MAX_PATH){
	   strcpy(string, "C:\\temp\\malloc1.c"); /* Nutzung */
	   printf( string );
   }

   free( string );
   printf( "\nMemory freed\n" );
   getchar();
}

/*
_MAX_PATH  = 260
Memory space 260 Byte allocated for path name
C:\temp\malloc1.c
Memory freed
*/
