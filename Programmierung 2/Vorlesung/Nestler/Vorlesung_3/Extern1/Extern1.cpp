
// C functions and data can be accessed only if they are
// previously declared as having C linkage. However, 
// they must be defined in a separately compiled 
// translation unit.

// Microsoft C++ supports the strings "C" and "C++" in
// the string-literal field. The following example shows
// alternative ways to declare names that have C linkage:

#include <stdio.h>
#include <iostream>

using namespace std;

// Declare printf with C linkage.
extern "C" int printf( const char *fmt, ... );

//  Declare the two functions ShowChar and GetChar
//   with C linkage.
extern "C"
{
    char ShowChar( char ch );
    char GetChar( void );
}

//  Define the two functions ShowChar and GetChar
//   with C linkage.
extern "C" char ShowChar( char ch )
{
    putchar( ch );
    return ch;
}

extern "C" char GetChar( void )
{
    char ch;
    ch = getchar();
    return ch;
}

// Declare a global variable, errno, with C linkage.
extern "C" int errno;
  
void main(){ 
	    char c; int i;
		ios::sync_with_stdio();  // iostream works wirth stdio.h
        printf("Zeichen eingeben : ");
        c = ShowChar(GetChar());
		i = printf("\nc = %c\n", c);
        std::cin.get();
}

/*
Zeichen eingeben : A
A
c = A
*/