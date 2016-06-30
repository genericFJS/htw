
#include <iostream>   // INH8.CPP - Aufweichen der private-Ableitung
using namespace std;

class base{ public:     base(int k=0):j(k),i(k),p(k){};
						~base(){};
                     	void pubB();
                        void pubB(int); //ueberladen
						int j;
	        private:   	void privB();
						int i;
	        protected: 	void protB();
						int p;
	  };

class derived:private base{ public: derived(int d):base(d){};
				~derived(){};
				base::pubB; //hier als public !!
				base::j;    //hier als public !!
				base::p;
		//		base::i;    //nicht moeglich !!
                            public:  void pubD();
			        private: void privD();
};

void out(base &b){cout<<"out"<<endl;
                  b.pubB();
				  b.pubB(5);
              //  b.privB();
              //  b.protB(); 
};

void base::pubB(){ cout<<"base pubB()"<<endl;    }

void base::pubB(int i){ cout<<"base pubB(i), i="<<i<<endl; }

void base::privB(){ cout<<"base privB()"<<endl;  }

void base::protB(){ cout<<" base protB()"<<endl; }

void derived::pubD(){ cout<<"derived pubD()"<<endl; }

void derived::privD(){ cout<<"derived privD()"<<endl; }

void main(){ 
	        derived d1(1);
			d1.pubB();
			d1.pubB(2);
			cout<<"d1.j = "<<d1.j<<endl;
			cout<<"d1.p = "<<d1.p<<endl;
         // base b5(d1);               // Error, kein Zugriff !
			base b6=(base)d1;
	     // base   *b1=&d1;           // Error, kein Zugriff !
	     // base   &b2=d1;            // Error, kein Zugriff !
	        base   *b3=(base *)&d1;
	        base   &b4=(base)d1;
	     // out(d1);                  // Error, kein Zugriff !
	        out((base &)d1);
}
