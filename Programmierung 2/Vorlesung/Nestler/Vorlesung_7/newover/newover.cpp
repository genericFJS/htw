#include <iostream>   // Newover.cpp
using namespace std;

class Demo {
  private:
    char name[32];
  public:
    Demo(const char *str=""){
	    strncpy(name,str,32); name[31]='\0';
	}
	void *operator new(size_t);
	void operator delete(void *);
	friend ostream& operator<<(ostream &, Demo &);
};

void *Demo::operator new(size_t size){
     cerr<<"new fuer Demo gerufen!\n";
	 void *ptr=::new char[size]; // globales new
	 return ptr;
}

void Demo::operator delete(void *ptr){
     cerr<<"delete fuer Demo gerufen!\n";
	 ::delete[] ptr; // globales delete gerufen
}

ostream& operator<<(ostream & cout, Demo & d){
     return cout<<d.name;
}

Demo demo1("global object");

void main(){
     Demo *dPtr=new Demo("dynamic object");
	 cout<<"demo1: "<<demo1<<'\n';
	 cout<<"*dPtr: "<<*dPtr<<'\n';
	 delete dPtr;
	 cin.get();
}
/*
new fuer Demo gerufen!
demo1: global object
*dPtr: dynamic object
delete fuer Demo gerufen!
*/