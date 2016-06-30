#include <iostream>
#include <iomanip>
#include <string>
#include <errno.h>
#include <limits.h>
#include <cstdlib>

// #include <limits.h>
using namespace std;

class ea {
	char sc;
	unsigned char uc;
	short ss;
	unsigned short us;
	int si;
	unsigned int ui;
	long sl;
	unsigned long ul;
	float f;
	double d;
	
public:
	void einaus() {
		
		cout << "Eingabe und Ausgabe der Grundatentypen" << endl;

		// nur 1 Zeichen nach char einlesbar, wird als ASCII-Zeichen interpretiert, 
		// z.B. A oder Alt+255 (Ziffernblock)
		cout << "char sc = "; cin >> sc; cin.clear(); cin.ignore(INT_MAX, '\n'); 
		cout << "&sc = " << setw(16) << setfill('0') << hex << (unsigned long long)(&sc) 
			 << "  sc = " << sc << "  sc = " << dec << (int)sc 
			 << "  sc = " << showbase << setbase(16) << ((int)sc & 0x000000FF) << endl;

		// nur 1 Zeichen nach unsigned char einlesbar, wird als ASCII-Zeichen interpretiert, 
		// z.B. A oder Alt+255 (Ziffernblock) 
		cout << "char uc = "; cin >> uc; cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "&uc = " << setw(16) << setfill('0') << hex << (unsigned long long)(&uc)
			 << "  uc = " << uc << "  uc = " << dec << (int)uc
			 << "  uc = " << hex << showbase << (int)uc << endl;
		
		cout << "short ss = "; cin >> ss; cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "&ss = " << setw(16) << setfill('0') << hex << (unsigned long long)(&ss)
			 << "  ss = " << dec << ss << "  ss = " << hex << showbase << ss << endl;

		cout << "unsigned short us = "; cin >> us; cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "&us = " << setw(16) << setfill('0') << hex << (unsigned long long)(&us)
			 << "  us = " << dec << us << "  us = " << hex << showbase << us << endl;

		cout << "int si = "; cin >> si; cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "&si = " << setw(16) << setfill('0') << hex << (unsigned long long)(&si)
			<< "  si = " << dec << si << "  si = " << hex << showbase << si << endl;

		cout << "unsigned int ui = "; cin >> ui; cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "&ui = " << setw(16) << setfill('0') << hex << (unsigned long long)(&ui)
			 << "  ui = " << dec << ui << "  ui = " << hex << showbase << ui << endl;

		cout << "long sl = "; cin >> sl; cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "&sl = " << setw(16) << setfill('0') << hex << (unsigned long long)(&sl)
			 << "  sl = " << dec << sl << "  sl = " << hex << showbase << sl << endl;

		cout << "unsigned long ul = "; cin >> ul; cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "&ul = " << setw(16) << setfill('0') << hex << (unsigned long long)(&ul)
			 << "  ul = " << dec << ul << "  ul = " << hex << showbase << ul << endl;

		cout << "float f = "; cin >> f; cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "&f  = " << setw(16) << setfill('0') << hex << (unsigned long long)(&f)
			<< "   f = " << setw(20) << fixed << setprecision(10) << setfill('_') << f << endl;

		// in C++ laesst sich (f & 0xFFFFFFFF) nicht compilieren !
		//	 << "  IEEE f = " << setw(16) << setbase(16) << showbase << (f & 0xFFFFFFFF) << endl;

		cout << "double d = "; cin >> d; cin.clear(); cin.ignore(INT_MAX, '\n');
		cout << "&d  = " << setw(16) << setfill('0') << hex << (unsigned long long)(&d)
			<< "   d = " << setw(20) << fixed << setprecision(10) << setfill('_') << d << endl;

		// --------------------------------------------------------------------------------------------

		const static int l = 128;
		char vb[l];
		size_t ie = 0;
		string s;

		cout << " sc = ";  cin.getline(vb, sizeof(vb), '\n');
		sc = (char)atoi(vb);
		cout << " sc = " << dec << (int)sc << "  sc = " << hex << showbase << ((int)sc & 0x000000FF) << endl;

		cout << " uc = ";  cin.getline(vb, sizeof(vb), '\n');
		uc = (unsigned char)atoi(vb);
		cout << " uc = " << dec << (int)uc << "  uc = " << hex << showbase << (int)uc << endl;
		if (errno == ERANGE)
			cout << "Overflow condition occured" << endl;

		cout << " ss = ";  cin.getline(vb, sizeof(vb), '\n');
		ss = atoi(vb);
		cout << " ss = " << dec << ss << "  ss = " << hex << showbase << ss << endl;

		cout << " us = ";  cin.getline(vb, sizeof(vb), '\n');
		us = atoi(vb);
		cout << " us = " << dec << us << "  us = " << hex << showbase << us << endl;

		// mit char *
		cout << " si = ";  cin >> setw(sizeof(vb)) >> vb;  // cout << " vb = " << vb << endl;                 
		si = atoi(vb); 
		cout << " si = " << dec << si << "  si = " << hex << showbase << si << endl;
	
		// stoi, mit string
		cout << " ui = ";  cin >> s;       // cout << " s = " << s << endl;
		ui = stoi(s, &ie, 10);
		cout << " ui = " << dec << ui << "  ui = " << hex << showbase << ui << endl;

		// stol
		cout << " sl = "; cin >> s;
		sl = stol(s, &ie, 10);
		cout << " sl = " << dec << sl << "  sl = " << hex << showbase << sl << endl;

		// stul
		cout << " ul = "; cin >> s; 
		ul = stol(s, &ie, 10);
		cout << " ul = " << dec << ul << "  ul = " << hex << showbase << ul << endl;

		// stof
		cin.clear();  cin.ignore(INT_MAX, '\n');
		cout << " f = "; getline(cin, s, '\n');
		f = stof(s, &ie);
		cout << "   f = " << setw(20) << fixed << setprecision(10) << setfill('_') << f << endl;

		// stod
		cout << " d = "; getline(cin, s, '\n');
		d = stod(s, &ie);
		cout << "   d = " << setw(20) << fixed << setprecision(10) << setfill('_') << d << endl;
	}
};

int main() {
	ea ea1;
	ea1.einaus();
	cin.get();
	return 0;
}

/*
Eingabe und Ausgabe der Grundatentypen
char sc =  
&sc = 0000006eecf3f818  sc =    sc = -1  sc = 0xff
char uc =  
&uc = 00000x6eecf3f819  uc =    uc = 255  uc = 0xff
short ss = -1
&ss = 00000x6eecf3f81a  ss = -1  ss = 0xffff
unsigned short us = -1
&us = 00000x6eecf3f81c  us = 65535  us = 0xffff
int si = -1
&si = 00000x6eecf3f820  si = -1  si = 0xffffffff
unsigned int ui = -1
&ui = 00000x6eecf3f824  ui = 4294967295  ui = 0xffffffff
long sl = -1
&sl = 00000x6eecf3f828  sl = -1  sl = 0xffffffff
unsigned long ul = -1
&ul = 00000x6eecf3f82c  ul = 4294967295  ul = 0xffffffff
float f = -0.1
&f  = 00000x6eecf3f830   f = _______-0.1000000015
double d = -0.1
&d  = 00000x6eecf3f838   d = _______-0.1000000000
sc = -1
sc = -1  sc = 0xff
uc = -1
uc = 255  uc = 0xff
ss = -1
ss = -1  ss = 0xffff
us = -1
us = 65535  us = 0xffff
si = -1
si = -1  si = 0xffffffff
ui = -1
ui = 4294967295  ui = 0xffffffff
sl = -1
sl = -1  sl = 0xffffffff
ul = -1
ul = 4294967295  ul = 0xffffffff
f = -0.1
f = _______-0.1000000015
d = -0.1
d = _______-0.1000000000
*/