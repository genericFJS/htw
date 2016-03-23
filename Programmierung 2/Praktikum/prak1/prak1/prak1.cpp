#include "stdafx.h"
#include <iostream>
#include <iomanip>
using namespace std;

void printASCII() {
	int i;
	for (i = 0; i<4; i++)
		cout << "|dec hex Char ";
	cout << "|" << endl;
	for (i = 0; i<32; i++)
	{
		cout << endl << "|";
		for (int j = 0; j < 128; j += 128 / 4)
		{
			cout << setw(3) << dec << (i + j) << " " << setw(3) << hex << (i + j);
			if (isgraph(j + i))
				cout << setw(5) << (char)(j + i) << " |";
			else 
				cout << setw(5) << "."<<" |";
		}
	}
}

int main()
{
	printASCII();
	cin.get();
    return 0;
}

