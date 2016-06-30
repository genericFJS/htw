// Inline.cpp
#include <iostream>

using namespace std;

#define MAX(A,B)((A)>(B)?(A):(B))

inline int max(int a, int b){ return a>b?a:b ; }

void main(){ 
	int x=1, xi=x, y=2, yi=y;

	cout<<"Makro mit Seiteneffekten:"<<endl;
    	cout<<"Makro  MAX(++x,++y)="<<MAX(++x,++y)<<endl;
	cout<<"x = "<<x<<"   y = "<<y<<'\n'<<'\n';
	
    	cout<<"Inline max(++xi,++yi)="<<max(++xi,++yi)<<endl;
	cout<<"xi= "<<xi<<"   yi= "<<yi<<endl;
	cin.get();
}

/*
Makro mit Seiteneffekten:
Makro  MAX(++x,++y)=4
x = 2   y = 4

Inline max(++xi,++yi)=3
xi= 2   yi= 3
*/