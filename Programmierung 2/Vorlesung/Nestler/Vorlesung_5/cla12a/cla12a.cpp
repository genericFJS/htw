#include <iostream>               // cla12a.cpp

using namespace std;

class s {	// static class 
		  static unsigned long y;
  public:  
	      static void summe(unsigned long x=0UL){ y+=x; }

	      static unsigned long give(){ return y; }
};

unsigned long s::y=10; //Definition, obwohl s::y private

void main(){
  cout<<"s::y="<<s::give()<<endl;  
  s::summe(5);                   
  s::summe(10);                    
  cout<<"s::y="<<s::give()<<endl;   
  cin.get();
}

/*
s::y=10
s::y=25
*/