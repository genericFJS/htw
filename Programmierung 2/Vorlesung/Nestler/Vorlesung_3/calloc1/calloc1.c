/* CALLOC1.C: This program uses calloc to allocate space for
 * 40 long integers. It initializes each element to zero.
 */
#include <stdio.h>
#include <malloc.h>

void main( void )
{
   long *buffer; long i=0;

   buffer = (long *)calloc( 40, sizeof( long ) );
   if( buffer != NULL )
      printf( "Allocated 40 long integers\n" );
   else
      printf( "Can't allocate memory\n" );

   for(i=0; i<40; i++) buffer[i]=i; /* Nutzung */

   /* Provozieren eines Debug-Errors: */
   buffer[40] = 40; /* unzulaessiger Index */

   free( buffer );
   getchar();
}

/*
Allocated 40 long integers
*/
