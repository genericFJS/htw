#include <iostream>

using namespace std;

class ratio {	long zaehl, nenn;
		public:	ratio(long z=0L, long n=0L):zaehl(z),nenn(n){};
				~ratio(){ cout<<"Destruktor ratio"<<endl; };
		friend ostream &operator<<(ostream &, ratio &);
};

class object{
		public: virtual void aus(){};
		
		// virtual bewirkt den Aufruf der Destruktoren auch der 
		// abgeleiteten Klassen !
	    	virtual ~object(){		//  /* virtual */ testen !
			cout<<"virtueller Destruktor von object"<<endl;}
};

ostream &operator<<(ostream & cout, ratio &z){
	cout<<z.zaehl<<"  "<<z.nenn;
	return cout;
};
								
class intObject : public object {
		public: intObject(int x=0):wert(x){};
			~intObject(){ cout<<"Destruktor intObject"<<endl; }
			int wert;
			void aus(){ cout<<wert<<endl; }
};

class charptrObject : public object {
		public: charptrObject(char *s=""):adr(s){}
			~charptrObject(){ 
				cout<<"Destruktor charptrObject"<<endl; }
			char *adr;
			void aus(){ cout<<adr<<endl; }
};

class ratioObject : public ratio, public object {
		public: ratioObject(long z=0L, long n=1L):ratio(z,n){};
			~ratioObject(){ cout<<"Destruktor ratioObject"<<endl; }
			void aus(){ cout<<*this<<endl; }
};

void main(){
	object *feld[3];
	feld[0]=new intObject(4711);
	feld[1]=new charptrObject("HTW");
	feld[2]=new ratioObject(3,4);
	feld[0]->aus();
	feld[1]->aus();
	feld[2]->aus();
	delete feld[0]; // Destruktoren von object und intObject
	delete feld[1]; // Destruktoren von object und charptrObject
	delete feld[2]; // Destruktoren von object, ratioObject u. ratio
	cin.get();
}

/*
4711
HTW
3  4
Destruktor intObject		// nur durch virtual Destruktor
virtueller Destruktor von object
Destruktor charptrObject	// nur durch virtual Destruktor
virtueller Destruktor von object
Destruktor ratioObject		// nur durch virtual Destruktor
virtueller Destruktor von object
Destruktor ratio		// nur durch virtual Destruktor
*/