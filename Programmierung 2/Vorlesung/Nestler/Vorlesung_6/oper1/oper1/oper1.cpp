#include <iostream>   // oper1.cpp
using namespace std;

class intvec{
		size_t len;	  // Anzahl Vektorelemente
		int *vec;     // int-Vektor
	public:	
		intvec(size_t len=1):len(len),
                           vec(len?new int[len]:0){
	         for(size_t i=0; i<=len; (*this)[i++]=0); //i<=len; Fehler wird abgefangen
				                 // vec[i++]=0);      //i<=len; Fehler fuehrt zum Abbruch
        } 

		size_t getl() const{ return this?len:0; };    //this == 0 moeglich
		
		// operator[]
		/*const*/ int &operator[](size_t idx) const {
	       static int dummy;                          //dummy existiert auch ausserhalb von operator[]()
	       int *res=&dummy;                           //res ist Adresse von dummy
	       if(this){                                  //this == 0 moeglich
	          if(idx<len)res=vec+idx;                 //Index idx zulaessig ?
	          else cout<<"Index="<<idx<<" >= "<<len<<'\n';
	       }
	       else cout<<"Vektor existiert nicht\n";
		// return (*this)[idx];                      // rekursiv, Fehler
	       return *res;                               //vec[idx] oder dummy
        } 

		~intvec(){ if(this){ delete [] vec, vec=0, len=0; } } //this == 0 moeglich 
};

void main(){
	intvec num(10);
	for(size_t i=0; i<num.getl(); num[i]=i++);
	                    // <==>   num.operator[](i)=i++; //public-Methode von num

	for(size_t i=0; i<=num.getl(); i++){ // = ist falsch, jedoch kein Abbruch !
		cout<<num[i]<<endl;              // num.vec[i] mit Compile-Error, da vec private
	}
	
	//num[50]= nicht erlaubt bei const int &operator[]()
    num[50]=50;                          //falscher Index, d.h. dummy=50, kein Abbruch
	cout<<"num[50] = "<<num[50]<<endl;   //falscher Index, Ausgabe dummy, kein Abbruch

	intvec *pp = 0;    //pp als Nullzeiger
	(*pp)[0] = 5;      //pp->operator[](0) = 5; -->dummy = 5
	pp->~intvec();     //expliziter Aufruf des Destruktors
    delete pp; pp=0;   //impliziter Aufruf des Destruktors
	cin.get();
}

/*
Index=10 >= 10
0
1
2
3
4
5
6
7
8
9
Index=10 >= 10
0
Index=50 >= 10
Index=50 >= 10
num[50] = 50
Vektor existiert nicht
*/