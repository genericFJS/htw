#include <iostream>		//virt6_old.cpp
using namespace std;

class boote {   
	  int maxv;
  public: boote(int i):maxv(i){cout<<"Konstruktor boote\n"; } 
	  virtual void druckeboot(){ 
		  cout<<"maxv= "<<maxv<<" Knoten\n"; }
	  virtual ~boote(){};
};

class segelb : public boote {   
          int segelf;
  public: segelb(int i):boote(110),segelf(i){
			  cout<<"Konstruktor segelb\n";
	  }
	  virtual void druckeboot(){ 
	       cout<<"Segelflaeche= "<<segelf<<" qm\n"; }
	  virtual ~segelb(){};
};

class motorb : public boote {   
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
			  /* boote(15),*/ mannschaft(i){     // boote(15) mehrdeutig
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
		boote *bm=(motorb *)new segelbmitmotor(2); // mehrdeutig ohne (motorb *)
		bm->druckeboot();		//spaete Bindung
		cout<<"------------------------------------\n";
		boote *bs=(segelb *)new segelbmitmotor(2); // mehrdeutig ohne (segelb *)
		bs->druckeboot();		//spaete Bindung
		delete bm; delete bs;
		cin.get();
}

/*
Konstruktor boote
Konstruktor segelb
Konstruktor boote
Konstruktor motorb
Konstruktor segelbmitmotor
Bootsdaten:
Segelflaeche= 20 qm
PS= 30 PS
maxv= 110 Knoten
Manschaft= 2 Mann
------------------------------------
Konstruktor boote
Konstruktor segelb
Konstruktor boote
Konstruktor motorb
Konstruktor segelbmitmotor
Bootsdaten:
Segelflaeche= 20 qm
PS= 30 PS
maxv= 110 Knoten
Manschaft= 2 Mann
------------------------------------
Konstruktor boote
Konstruktor segelb
Konstruktor boote
Konstruktor motorb
Konstruktor segelbmitmotor
Bootsdaten:
Segelflaeche= 20 qm
PS= 30 PS
maxv= 110 Knoten
Manschaft= 2 Mann
*/