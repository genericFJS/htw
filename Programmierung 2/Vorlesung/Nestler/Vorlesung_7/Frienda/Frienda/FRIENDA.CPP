// FRIENDA.CPP - function als friend
#include <iostream>  
using namespace std;

class myClass {
  public:  
	   // YourFunction darf auf private/protected-Member
	   // von myClass zugreifen:
	   

	   myClass(int i=0):privateElem(i){
			     cout<<"Konstruktor myClass\n";
	   }
	   ~myClass(){cout<<"Destruktor myClass\n";};
	   int give_Elem(){ return privateElem; }
	   // ...
  private:
	   int privateElem;
	   // ...
	   friend void YourFunction(myClass& y, int i=0);
};

void YourFunction(myClass& y, int i){ y.privateElem=i; }

void main(){ 
	     myClass x;

	     cout<<"privateElem="<<x.give_Elem()<<endl;

	     YourFunction(x,5); // Zugriff auf x.privateElem

	     cout<<"privateElem="<<x.give_Elem()<<endl;

		 cin.get();
}

/*
Konstruktor myClass
privateElem=0
privateElem=5

Destruktor myClass
*/
