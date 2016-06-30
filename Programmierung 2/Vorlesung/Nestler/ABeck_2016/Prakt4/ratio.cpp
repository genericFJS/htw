#include <iostream> 

using namespace std;

// rationale Zahl, dargestellt durch Zaehler und Nenner
class ratio						
{  
	  int    zaehl, nenn;			// Zaehler, Nenner
  
  public: 
	  static int ggT(const int &n, const int &m) { // Rekursiver Algorithmus von Euklid
		  if (abs(m)>abs(n)) return abs(ggT(m, n)); // vertauschen von n und m
		  if (!m) return abs(n); // if(m == 0) return abs(n), Abbruch
		  return abs(ggT(m, n%m)); // rekursiver Schritt
	  }

	  ratio &kuerze() {				// Kuerzen
		  auto ggt = ggT(zaehl, nenn);
		  zaehl /= ggt, nenn /= ggt;
		  return *this;
	  }

	  static void kuerze(ratio &r) { // Kuerzen 
		  auto ggt = ggT(r.zaehl, r.nenn);
		  r.zaehl /= ggt, r.nenn /= ggt;
	  }

   ratio(int z=0, int n=1);			// Konstruktor mit default-Werten
   ratio(const ratio &);			// Kopierkonstruktor
   ~ratio();						// Destruktor

   ratio  &mult(const ratio &x);		// (*ths) = (*this) * x
   ratio  &div(const ratio &x);			// (*this) = (*this) / x
   ratio  &mult(int i);					// (*this) = (*this)*i
   ratio  &div(int i);					// (*this) = (*this)/i
   ratio  &add(const ratio &x);         // (*this) = (*this) + x
   ratio  &sub(const ratio &x);         // (*this) = (*this) - x
   ratio  &add(int i);                  // (*this) = (*this) + i
   ratio  &sub(int i);                  // (*this) = (*this) - i
   ratio  &minus();                     // (*this) = -(*this);

   static ratio  mult(const ratio &x1, const ratio &x2);  // return x1 * x2
   static ratio  div(const ratio &x1, const ratio &x2);   // return x1 / x2
   static ratio  mult(const ratio &x1, int i);		      // return x1 * i
   static ratio  div(const ratio &x1, int i);		      // return x1 / i
   static ratio  add(const ratio &x1, const ratio &x2);   // return x1 + x2
   static ratio  sub(const ratio &x1, const ratio &x2);   // return x1 - x2
   static ratio  add(const ratio &x1, int i);		      // return x1 + i
   static ratio  sub(const ratio &x1, int i);		      // return x1 - i
   static ratio  minus(const ratio &x1);		          // return -x1

   ratio  &display();                     // Memberfkt. Ausgabe
  
   auto    get_zaehl() -> const int { return zaehl; }    // Lesen zaehl
   auto    get_nenn() -> const int { return nenn; }      // Lesen nenn
   auto   set_zaehl(int z=0) -> void { zaehl=z; }        // Schreiben zaehl
   auto   set_nenn(int n = 1) -> void { n ? nenn = n : 1; }
};

ratio ratio::mult(const ratio &x1, const ratio &x2){		// return x1*x2
      return ratio(x1.zaehl*x2.zaehl,x1.nenn*x2.nenn).kuerze(); 
}

ratio ratio::div(const ratio &x1, const ratio &x2){			// return x1/x2
	  return ratio (x1.zaehl*x2.nenn,x1.nenn*x2.zaehl).kuerze(); 
}

ratio ratio::mult(const ratio &x1, int i) {					// return x1+i
	return ratio(x1.zaehl*i, x1.nenn).kuerze();
}

ratio ratio::div(const ratio &x1, int i){ // return x1/i (i!=0), sonst return x1
	return ratio(x1.zaehl, i?x1.nenn*i:x1.nenn).kuerze();
}

ratio ratio::add(const ratio &x1, const ratio &x2){			// return x1+x2
      return ratio(x1.zaehl*x2.nenn+x2.zaehl*x1.nenn, x1.nenn*x2.nenn).kuerze();
}

ratio ratio::sub(const ratio &x1, const ratio &x2){			// return x1-x2
      return ratio(x1.zaehl*x2.nenn-x2.zaehl*x1.nenn, x1.nenn*x2.nenn).kuerze();
}

ratio ratio::add(const ratio &x1, int i) {			// return x1 + i
	return ratio(x1.zaehl + i*x1.nenn, x1.nenn).kuerze();
}

ratio ratio::sub(const ratio &x1, int i) {			// return x1 - i
	return ratio(x1.zaehl - i*x1.nenn, x1.nenn).kuerze();
}

ratio ratio::minus(const ratio &x1) {				// return -x
	return ratio(-x1.zaehl, x1.nenn).kuerze();
}

//------------------------------------------------------------------------------
ratio::ratio(int z, int n):zaehl(z),nenn(n?n:1)		//Ueberladener Konstruktor
{ 
  cout<<"Konstruktor ratio(int, int) gerufen"<<endl;
  if(!n){ cerr<<"Nenner == 0, wird auf 1 gesetzt !\n"; }
  kuerze();
}
	
ratio::ratio(const ratio &r):zaehl(r.zaehl),nenn(r.nenn) //Kopierkonstruktor
{
	cout<<"Kopierkonstruktor ratio(ratio &) gerufen"<<'\n';   
}

ratio::~ratio() //Destruktor
{
 cout<<"Destruktor ~ratio() gerufen"<<endl;
}

ratio &ratio::display() 
{
	cout << zaehl << " / " << nenn << endl; 
	return *this;
}
				
ratio &ratio::mult(const ratio &x)			// (*this) = (*this) * x
{ 
	zaehl *= x.zaehl; nenn *= x.nenn; return kuerze(); 
}

ratio &ratio::div(const ratio &x)			// (*this) = (*this) / x
{ 
	zaehl *= x.nenn; nenn *= x.zaehl; return kuerze();
}

ratio &ratio::mult(int i)				// (*this)=(*this)*i
{
	zaehl *= i; return kuerze();
}

ratio &ratio::div(int i)				// (*this)=(*this)/i
{
	nenn *= i; return kuerze();
}

ratio &ratio::minus()                   // (*this) = -(*this);
{
	 zaehl=-zaehl; return *this;
}

ratio  &ratio::add(const ratio &x)				// (*this) = (*this) + x
{ 
	zaehl = zaehl*x.nenn + nenn*x.zaehl; nenn *= x.nenn;
	return kuerze();
}

ratio  &ratio::sub(const ratio &x)				// (*this) = (*this) - x
{ 
	zaehl = zaehl*x.nenn - nenn*x.zaehl; nenn *= x.nenn;
	return kuerze();
}

ratio  &ratio::add(int i)				// (*this) = (*this) + i
{ 
	zaehl += i*nenn; return kuerze(); 
}

ratio  &ratio::sub(int i)				// (*this) = (*this) - i
{ 
	zaehl -= i*nenn; return kuerze(); 
}


class f1{
	ratio *a1;
	size_t anz;
public:
	f1():a1(0),anz(0){}
	f1(ratio r, size_t anz=0):a1(anz?new ratio[anz]:0),anz(anz){
		for(size_t i=0; i<anz; i++) a1[i]=r;
	}
	f1(f1 &f):a1(f.anz?new ratio[f.anz]:0),anz(f.anz){
		for(size_t i=0; i<anz; i++) a1[i] = f.a1[i];
	}
	~f1(){ 
		delete [] a1; a1=0; anz=0; 
		cout<<"Destruktor f1\n";
	}
	ratio get(size_t i){ 
		if(i<anz)
			return a1[i];
		cout<<"Index "<<i<<" >= "<<anz<<endl;
	    return ratio(0,1);
	}
	void set(size_t i, ratio r){ 
		if(i<anz) 
			a1[i]=r;
		else 
			cout<<"Index "<<i<<" >= "<<anz<<endl;
	}
};

class f2{
	 ratio **a2;
	 size_t i, j;
public:
	f2():a2(0),i(0),j(0){};

	f2(ratio r, size_t i=0, size_t j=0):a2(i?new ratio *[i]:0),i(i),j(j){
		for(size_t l=0; l<i; l++){ a2[l]=j?new ratio[j]:0; //Initialisierung
		                           for(size_t m=0; m<j; m++) a2[l][m] = r;
		}
	}

	f2(f2 &f):a2(f.i?new ratio *[f.i]:0),i(f.i),j(f.j){

		for(size_t l=0; l<i; l++){ a2[l]=j?new ratio[j]:0; //Initialisierung
			for(size_t m=0; m<j; m++){
				a2[l][m] = f.a2[l][m];
			}
		}
	}

	~f2(){ for(size_t l=0; l<i; l++) delete [] a2[l];
	       delete [] a2; a2 = 0; i = 0; j = 0;
		   cout<<"Destruktor f2\n";
	}

	ratio get(size_t i, size_t j){ 
		if((i<this->i) && (j<this->j))
			return a2[i][j];
		
		if(i>=this->i)
				  cout<<"1.Index "<<i<<" >= "<<this->i<<endl;
		if(j>=this->j)
				  cout<<"2.Index "<<j<<" >= "<<this->j<<endl;
		return ratio(0,1);
	}

	void set(size_t i, size_t j, ratio r){ 
		if((i<this->i) && (j<this->j))
			a2[i][j]=r;
		else {
			  if(i>=this->i)
				  cout<<"1.Index "<<i<<" >= "<<this->i<<endl;
			  if(j>=this->j)
				  cout<<"2.Index "<<j<<" >= "<<this->j<<endl;
		}	
	}
};

void main()
{
// -(((((1/2)*(3/5)*2+2/5)/(1/8)-5)+3)/2)

  ratio *r1 = new ratio(1,2), *r2 = new ratio(3,5), *r3 = new ratio(2,5), *r4 = new ratio(1,8);
  r1->mult(*r2).display().mult(2).display().add(*r3).display().div(*r4).display().sub(5).display().add(3).display().div(2).display().minus().display();
  r1->set_zaehl(1);
  r1->set_nenn(2);
  (ratio::minus(ratio::div(ratio::add(ratio::sub(ratio::div(ratio::add(ratio::mult(ratio::mult(*r1,*r2),2),*r3),*r4),5),3),2))).display();

  f1 *feld = new f1(*r1, 5);
  feld->set(1, *r2);
  cout<<feld->get(1).get_zaehl()<<" / "<<feld->get(1).get_nenn()<<endl;
  f1 *feld1 = new f1(*feld);

  f2 *feld2 = new f2(*r2, 3, 4);
  feld2->set(2,2,*r2);
  cout<<feld2->get(2,2).get_zaehl()<<" / "<<feld2->get(2,2).get_nenn()<<endl;
  f2 *feld3 = new f2(*feld2);

  delete r1; delete r2; delete r3; delete r4; 
  delete feld; delete feld1; delete feld2; delete feld3;
  cin.get();
}
