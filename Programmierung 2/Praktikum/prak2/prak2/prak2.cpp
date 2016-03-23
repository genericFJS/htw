#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

signed char		sc;
unsigned char	uc;
signed short	ss;
unsigned short	us;
signed int		si;
unsigned int	ui;
signed long		sl;
unsigned long	ul;
float			f;
double			d;

void printGet() {
	const static int l = 128;
	char vb[l];
	size_t ie = 0;
	string s;

	cout << " signed char sc = ";
	cin.getline(vb, sizeof(vb), '\n');
	sc = (unsigned char) atoi(vb);
	cout << " Adresse: " << setw(16) << setfill('0') << 
		hex << (unsigned long long)(&sc) << " char:" << 
		dec << (char)sc << " hex:" << 
		hex << showbase << ((int)sc & 0x000000FF) << endl;
	cout << setw(32) << setfill('-') << "-" << endl;

	/*cout << " unsigned char uc = ";
	cin.getline(vb, sizeof(vb), '\n');
	uc = atoi(vb);
	cout << " &uc = " << setw(16) << setfill('0') <<
		hex << (unsigned long long)(&uc) << " uc = " <<
		dec << (int)uc << " uc = " <<
		hex << showbase << ((int)uc & 0x000000FF) << endl;
	cout << setw(32) << setfill('-') << "-" << endl;

	cout << " signed short ss = ";
	cin.getline(vb, sizeof(vb), '\n');
	ss = atoi(vb);
	cout << " &ss = " << setw(16) << setfill('0') <<
		hex << (unsigned long long)(&ss) << " ss = " <<
		dec << (int)ss << " ss = " <<
		hex << showbase << ((int)ss & 0x000000FF) << endl;
	cout << setw(32) << setfill('-') << "-" << endl;

	cout << " unsigned short us = ";
	cin.getline(vb, sizeof(vb), '\n');
	us = atoi(vb);
	cout << " &us = " << setw(16) << setfill('0') <<
		hex << (unsigned long long)(&us) << " us = " <<
		dec << (int)us << " us = " <<
		hex << showbase << (int)us << endl;
	cout << setw(32) << setfill('-') << "-" << endl;*/
}



int main()
{
	printGet();
	cin.get();
    return 0;
}

