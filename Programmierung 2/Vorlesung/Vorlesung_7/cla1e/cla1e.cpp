#include <iostream>            //cla1e.cpp

using namespace std;

class foo {
   public:
	foo(size_t w=0):b(w){};

	class bar {               //static
		 public: static char *c;
		         size_t w;
			 bar(size_t w):w(w){};
	} b; //Datenmember b
};

char *foo::bar::c="TU Dresden";  // Definition

void main(){

    foo::bar::c="HTW Dresden";   // Wertzuweisung

    cout<<"foo::bar::c = "<<foo::bar::c<<endl;
	
    foo f;                       // Objekt f

    f.b.w=5;	// Wertzuweisung alternativ
    cout<<"f.b.w       = "<<f.b.w<<endl;
    cin.get();
}

/*
foo::bar::c = HTW Dresden
f.b.w       = 5
*/