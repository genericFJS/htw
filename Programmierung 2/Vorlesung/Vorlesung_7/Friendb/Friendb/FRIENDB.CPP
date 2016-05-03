#include <iostream>  // friendb, eine andere Klasse als Freund

using namespace std;

class YourOtherClass;

class YourClass {

	   friend class YourOtherClass;

  public:  
	   YourClass(int i=0):topSecret(i){
			cout<<"Konstruktor YourClass"<<endl;
	   }
	   ~YourClass(){
			cout<<"Destruktor YourClass"<<endl;
	   }
	   int give_topSecret(){ return topSecret; }

  private: 
	   int topSecret;
};

class YourOtherClass {
  public: 
	  YourOtherClass(){
			cout<<"Konstruktor YourOtherClass"<<endl;
	  }
	  ~YourOtherClass(){
			cout<<"Destruktor YourOtherClass"<<endl;
	  }
	  void changeIt(YourClass& yc){ yc.topSecret++; }
};

void main(){ 
	     YourClass x(10);
	     YourOtherClass y;
	     cout<<"x.topSecret="<<x.give_topSecret()<<endl;
	     y.changeIt(x); // x.topSecret ändern als friend
	     cout<<"x.topSecret="<<x.give_topSecret()<<endl;
		 cin.get();
}

/*
Konstruktor YourClass
Konstruktor YourOtherClass
x.topSecret=10
x.topSecret=11

Destruktor YourOtherClass
Destruktor YourClass
*/
