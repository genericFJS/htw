#include <iostream>		//virt6.cpp
using namespace std;

class boote {   
	  int maxv;
  public: boote(int i):maxv(i){cout<<"Konstruktor boote\n"; } 
	  virtual void druckeboot(){ 
		  cout<<"maxv= "<<maxv<<" Knoten\n"; }
	  virtual ~boote(){};
};

class segelb : virtual public boote {   
          int segelf;
  public: segelb(int i):boote(110),segelf(i){
			  cout<<"Konstruktor segelb\n";
	  }
	  virtual void druckeboot(){ 
	       cout<<"Segelflaeche= "<<segelf<<" qm\n"; }
	  virtual ~segelb(){};
};

class motorb : virtual public boote {   
          int ps;
  public: motorb(int i):boote(220), ps(i){ 
		cout<<"Konstruktor motorb\n"; }
	  virtual void druckeboot(){ cout<<"PS= "<<ps<<" PS\n"; 
	  }
	  virtual ~motorb(){};
};

class segelbmitmotor : public segelb, public motorb {
	  int mannschaft;
  public: segelbmitmotor(int i):segelb(20),motorb(30),
			  boote(15), mannschaft(i){ 
		cout<<"Konstruktor segelbmitmotor\n"; 
	  }
	  void druckeboot(){ cout<<"Bootsdaten:\n";
			     segelb::druckeboot();
			     motorb::druckeboot();
			     boote::druckeboot();
			     cout<<"Manschaft= "
			         <<mannschaft
			         <<" Mann\n";
	  }
	  virtual ~segelbmitmotor(){};
};

void main(){ segelbmitmotor sm(2);
	        sm.druckeboot();		//fruehe Bindung
		cout<<"------------------------------------\n";
		boote *b = new segelbmitmotor(2);
		b->druckeboot();		//spaete Bindung
		delete b;
		cin.get();
}

/*
Konstruktor boote
Konstruktor segelb
Konstruktor motorb
Konstruktor segelbmitmotor
Bootsdaten:
Segelflaeche= 20 qm
PS= 30 PS
maxv= 15 Knoten
Manschaft= 2 Mann
------------------------------------
Konstruktor boote
Konstruktor segelb
Konstruktor motorb
Konstruktor segelbmitmotor
Bootsdaten:
Segelflaeche= 20 qm
PS= 30 PS
maxv= 15 Knoten
Manschaft= 2 Mann
*/