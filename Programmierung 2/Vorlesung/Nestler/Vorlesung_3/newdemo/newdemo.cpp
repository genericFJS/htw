#include <iostream> 
#include <new.h>
//#include <process.h>
// #define N 19400000000UL  // error C2148: total size of array must not exceed 0x7fffffff bytes
#define N 0x7fffffff        // Platform x64: OK
using namespace std;

//Fehlerbehandlungsroutine:
int MyNewHandler(size_t size) //size: angeforderter Speicherplatz
{
    clog<<"Dynamic memory requested: "
		<<(unsigned long)size
		<<" Bytes, allocation failed\n";
    return 0; //Rueckgabe  0: kein erneuter Versuch Allokierung
}             //Rueckgabe !0: Wiederholung der Allokierung

void main()
{
 	_set_new_handler(MyNewHandler); // Zeiger MyNewHandler 

 	char *bigString = nullptr;
 	try {                           // error: total size of array must not exceed 0x7fffffff bytes
     	bigString=new char[N]; 		// Fehler: 1.Aufruf MyNewHandler 
		for(size_t i=0; i<N-1; i++)	// auffuellen
			bigString[i]='#';       // mit '#'
	     bigString[N-1] = 0;		// am Ende: '\0'
	
 	     cout<<"adr bigString = "<<hex<<(int *)(bigString)<<endl;
	//   cout<<"    bigString = "<<bigString<<endl;
		 delete[] bigString; bigString = nullptr;
 	}
 	catch(...){
     		clog<<"caught exception 1\n"; 		
 	}
 	
  // Retten des Zeigers auf bisherige Fehlerbehandlungsroutine und
 	_PNH old_handler = _set_new_handler(0);	//Fehlerbeh. deaktiviert
	try {
		bigString = new char[N]; // total size of array must not exceed 0x7fffffff bytes
		delete [] bigString; bigString = nullptr; 
	}
	catch(...){
		    cerr<<"caught exception 2\n"; 
 	}
	
	_set_new_handler(old_handler);  // MyNewHandler wieder aktiviert
	_set_new_mode(1);				// Fehlerbehandlung fuer malloc 
	
	char *s = (char *)malloc(N); 

	if(!s) cout<<"malloc("<<N<<") nicht erfolgreich !\n";
	free(s); s=nullptr;
	
	_set_new_mode(0);				// Fehlerbehandlung fuer new 
 	cin.ignore();
}

/*
adr bigString = 000000007FFF3070
*/