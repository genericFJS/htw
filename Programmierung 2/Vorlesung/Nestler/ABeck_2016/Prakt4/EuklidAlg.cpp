#include <iostream>
using namespace std;

// Der ggt(n,m) wird m, wenn n durch m teilbar, anderenfalls ist er 
// gleich dem ggt(m, Rest(n/m))
long ggT(long n, long m){ 
      if(abs(m)>abs(n)) return abs(ggT(m,n));
      if(!m) return abs(n);
      return abs(ggT(m,n%m));
}                                                  
// ggT(6,15) -> ggT(15,6) -> ggT(6,15%6) -> ggT(6,3) -> ggT(3,0) -> 3
//     n  m          n m         n    m         n m         n m   ggt


long Euklid(long a, long b){
	a = abs(a); b=abs(b);
	while(a*b){
		       if(a >= b) a = a % b;
			   else b = b% a;
	}
	return a + b;
}

void main(){
	int a = 0, b = 0;
	cout<<"ganze Zahl a = "; cin>>a; cin.clear(); cin.ignore(INT_MAX, '\n');
	cout<<"ganze Zahl b = "; cin>>b; cin.clear(); cin.ignore(INT_MAX, '\n');
	cout<<"   ggT( "<<a<<" , "<<b<<" ) = "<<ggT(a,b)<<endl;
	cout<<"Euklid( "<<a<<" , "<<b<<" ) = "<<Euklid(a,b)<<endl;
	cin.get();
}