#include <iostream>		//cla8.cpp
#include <stddef.h>

using namespace std;

class puffer{ 
				char *p;    //Puffer
				size_t lng; //Laenge in Byte
	public: 
		static int deflng;
	    
		puffer(int lng=deflng):p(new char[lng+1]), 
							   lng(lng){
			 cout<<"puffer-Konstruktor lng="
				 <<lng<<endl;
	     }

		~puffer(){ 
			cout<<"puffer-Destruktor  lng="
				 <<lng<<endl;
			delete [] p; p=0;
	     }
	  // ...
};

int puffer::deflng=1024;

void main(){
 puffer p1;         // wie puffer p1(1024);
 puffer::deflng=512;
 p1.deflng=2048;    // verwirrend, aber OK
 puffer p2;         // puffer p2(2048)
 puffer p3(256);    
 cin.get();
}

/*
puffer-Konstruktor lng=1024
puffer-Konstruktor lng=2048
puffer-Konstruktor lng=256

puffer-Destruktor  lng=256
puffer-Destruktor  lng=2048
puffer-Destruktor  lng=1024
*/