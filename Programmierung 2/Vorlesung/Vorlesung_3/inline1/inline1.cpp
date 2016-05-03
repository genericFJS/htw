#include <iostream>

using namespace std;

#define GENERATE_MAX(T) \
        inline T& MAX(T& a, T& b) \
		{ return a > b ? a : b; }

GENERATE_MAX(int);
GENERATE_MAX(double);
GENERATE_MAX(float);
GENERATE_MAX(char);
GENERATE_MAX(long);

void main(){
     int x=23, y=20;
	 cout<<"MAX("<<x<<","<<y<<") = "
	     <<MAX(x,y)<<endl;
	 cin.get();
}

/*
    MAX(23,20) = 23
*/