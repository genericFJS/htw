#include <iostream>
#include "Matrix.h"  
//http://www.stroustrup.com/Programming/Matrix/Matrix.h
//Titel: Einfuehrung in die Programmierung mit C++
//Bjarne Stroustrup
//ISBN: 978-3-8689-4005-3
//1224 Seiten 
//Erscheinungstermin: 3/2010
//Sprache: Deutsch
//€ 69,95 [D] 
//S.862 ff.

using namespace std;
using namespace Numeric_lib;

auto main() -> int {
    auto n1=0U, n2=0U;
	do {
		cout<<"Matrix-Dimension 1, n1 = "; cin>>n1; 
		cin.clear(); cin.ignore(INT_MAX, '\n');
		cout<<"Matrix-Dimension 2, n2 = "; cin>>n2; 
		cin.clear(); cin.ignore(INT_MAX, '\n');
	} while(n1<1U || n2<1U);

	Matrix<double,2> d2(n1,n2); // Matrix d2 dyn. anlegen

	for(auto i=0; i<d2.dim1(); i++)
		for(auto j=0; j<d2.dim2(); j++)
			d2[i][j] = (double)(i+j);

	auto i=2, j=3;
	cout<<((i<d2.dim1() && j<d2.dim2())?d2[i][j]:0.0)<<endl;
	cin.get();
}