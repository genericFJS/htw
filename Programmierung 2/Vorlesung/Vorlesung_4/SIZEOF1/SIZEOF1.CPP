#include <iostream>  // sizeof1.cpp

using namespace std;

// sizeof arbeitet waehrend der Compile-Time

void test(char *s1){
	 cout<<"sizeof(s1)  ="
	     <<sizeof(s1)<<'\n' 
	     <<"sizeof(*s1) =";
	     <<sizeof(*s1)<<endl;
};

void main(){ 
         char *z=new char[100];
	 strcpy(z,"123456789");
	 test(z);
	 cin.get();
};

/*
sizeof(s1)  =4
sizeof(*s1) =1
*/