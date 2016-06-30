#include <iostream>
using namespace std;

class musiker { public: 
					virtual void setvol(int value); 
};

class trompeter : public musiker { 
				public : 
					virtual void setvol(long value); // kein virtual-override
};

void musiker::setvol(int value){ cout<<"Musiker: "<<value<<endl; }

void trompeter::setvol(longt value){ 
	                               musiker::setvol((int)value);
	                               cout<<"Trompeter: "<<value<<endl; 
}

void main(){ 
	     
	     musiker *pm=new trompeter;
	     trompeter *pt=(trompeter *)pm;  // expliziter cast
	     pm->setvol(5);                  // Musiker: 5
	     pt->setvol(10L);                // Trompeter: 10
	     delete pm; pm = 0; pt = 0; 
		 cin.get();
	   }

/*
Musiker: 5
Musiker: 10
Trompeter: 10
*/