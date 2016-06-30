#include <iostream>

using namespace std;

#define N 6
int a[N];
auto main() -> int {
	a[5]=5;  
	*(a+4)=4;
	*(3+a)=3;
	2[a]=2;
	1[a]=1;
	0[a]=0;
	for(auto i=0; i<N; i++)
		  cout<<"a["<<i<<"]="<<i[a]<<endl;
	cin.get();
	return 0;
}

	    
