#include <iostream>      // refdem2.cpp

using namespace std;

int &change_int(int &x) {
	cout<<"here is x in change_int, x = "
		<<x<<'\n';
	return x;
}

void main(){
	int x(0);
	change_int(x)=5;          // wie x=5;
	change_int(x)=6;          // wie x=6;
	cout<<"final                    x = "
		<<x<<endl;
	cin.get();
}

/*
here is x in change_int, x = 0
here is x in change_int, x = 5
final                    x = 6
*/