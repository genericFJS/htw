#include <iostream> 
using namespace std;

class ratio						
{  
   int  zaehl, nenn;		// Zaehler, Nenner
 public: 
   void   kuerze(){
	   int ggt, i;
	   if(this){
         for(ggt=1, i=1;
             i<=(abs(zaehl)<=abs(nenn)?abs(zaehl):abs(nenn)); //Minimum
             !(nenn%i)&&!(zaehl%i)?ggt=i++:(ggt,i++));
         zaehl/=ggt, nenn/=ggt;
	   }
   }

   ratio(int z, int n=1):zaehl(z),nenn(n) //Konstruktor
   {
      if(!nenn) nenn=1;
      kuerze();
   }				
  
   ratio  operator*(const ratio &x){ // return *this * x
       ratio r(this->getzaehl()*x.getzaehl(),
		       this->getnenn()*x.getnenn()); 
	   r.kuerze();
       return r; // Kopie von r
   }                                        

   ratio  operator/(const ratio &x){ // return *this / x
      ratio r(this->getzaehl()*x.getnenn(),this->getnenn()*x.getzaehl()); 
	  r.kuerze();
      return r;	// Kopie von r
   }		

   ratio  operator+(const ratio &x){ // return *this + x
      ratio r(this->getzaehl()*x.getnenn()+x.getzaehl()*this->getnenn(),
              this->getnenn()*x.getnenn());
	  r.kuerze();
	  return r; // Kopie von r
   }

   ratio  operator-(const ratio &x){ // return *this - x
     ratio r(this->getzaehl()*x.getnenn()-x.getzaehl()*this->getnenn(),
             this->getnenn()*x.getnenn());
	 r.kuerze();
	 return r; // Kopie von r
   }

   ratio  operator-(){ // return -*this
	 ratio r(-this->zaehl, this->nenn); return r;
   }						      

   int    getzaehl() const { return zaehl; }   // Lesen zaehl
   int    getnenn() const { return nenn; }     // Lesen nenn

   static int _int(char *z){ //robuste Eingabe int ueber cin
	 int _(0);
	 char c('\n');
	 do {
		  if(c!='\n'){
			 cin.clear(); cin.ignore(INT_MAX,'\n');
		}
		cout<<(z?z:"Eingabe = "); cin>>_;
	 } while((c=cin.peek())!='\n');
     cin.clear(); cin.ignore(INT_MAX,'\n');
	 return _;
   }

   friend ostream &operator<<(ostream &cout, const ratio &r);
   friend istream &operator>>(istream &cin, ratio &r);
};

/*
ostream &operator<<(ostream &cout, const ratio &r){
	return cout<<r.getzaehl()<<" / "<<r.getnenn()<<'\n';
}

istream &operator>>(istream &cin, ratio &r){
	ratio rr(ratio::_int("zaehl = "), ratio::_int("nenn = "));
	r=rr; r.kuerze();
	return cin;
}
*/

//als friend von class ratio:
ostream &operator<<(ostream &cout, const ratio &r){
	return cout<<r.zaehl<<" / "<<r.nenn<<'\n';
}

istream &operator>>(istream &cin, ratio &r){
	r.zaehl = ratio::_int("zaehl = ");
	r.nenn  = ratio::_int("nenn = ");
    r.kuerze();
	return cin;
}


void main()
{
  ratio *r1 = new ratio(1,2), *r2 = new ratio(3,5), 
	    *r3 = new ratio(2,5), *r4 = new ratio(1,10);

  ratio r5 = *r1 * *r2 + *r3 - -*r4; 
  cout<<"r5 = "<<r5<<endl;

  r5 = ((r1->operator*(*r2)).operator+(*r3)).operator-((*r4).operator-());
  cout<<"r5 = "<<r5<<endl;

  cin>>*r1;
  operator>>(cin, *r1);

  cout<<"*r1 = "<<*r1;
  operator<<(operator<<(cout, "*r1 = "), *r1);

  cin.get();
}
