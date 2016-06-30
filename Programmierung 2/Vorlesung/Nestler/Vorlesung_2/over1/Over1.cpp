#include <iostream>
#include <iomanip>

using namespace std;

void foo(int, int);
void foo(int);
void foo(double, double);
void foo(double);

void main(){             foo(1,2);
						 foo(1);
						 foo(1.5, 2.5);
						 foo(1.1);
						 cin.get();
}

auto foo(int i, int j) -> void {  
	                     cout.flags(ios::fixed);
						 cout<<"foo("<<i<<","<<j<<")             = ";
			             cout<<setprecision(5);
                         cout<<1.0/double(i)+1.0/double(j)<<endl;
}

auto foo(int i) -> void {cout.setf(ios::fixed);
						 cout<<"foo("<<i<<")               = ";
						 cout<<setprecision(5);
						 cout<<1.0/double(i)<<endl;
}

auto foo(double i, double j) -> void { 
						 cout<<"foo("<<i<<","<<j<<") = "
			                 <<fixed<<setprecision(5)
                             <<1.0/i+1.0/j<<endl;
}

auto foo(double i) -> void { cout<<"foo("<<i<<")         = "
						         <<fixed<<setprecision(5)
						         <<1.0/i<<endl;
}

/*
foo(1,2)             = 1.50000
foo(1)               = 1.00000
foo(1.50000,2.50000) = 1.06667
foo(1.10000)         = 0.90909
*/

