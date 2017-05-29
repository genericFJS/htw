#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	int a = 'x';
	switch (a) {
	case 'a':
		a += 23;
		break;
	case 'b':
		a *= 2;
	default:
		a %= 4;
	}
	exit (0);
}