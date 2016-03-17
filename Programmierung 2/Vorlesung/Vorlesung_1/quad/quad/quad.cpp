#include <iostream>

using namespace std;

class quad {
	double x;
public:
	quad(double x = 0.0):x(x){
		cout<<"Konstruktor, x = "<<x<<endl;
	}

	~quad(){ cout<<"Destruktor quad\n"; }

	auto get_x() -> double { return x; }

	auto set_x(double x = 0.0) -> void { this->x = x; }

	// Funktion, die Variable x mit 1 oder 2 Faktoren
	// multipliziert
	auto mult(double y, double z=1.0) -> void { x = x*y*z; }
};

void main(){
	quad q1;

	auto x = 0.0;
	cout<<"x = "; cin>>x; 
	cin.clear(); cin.ignore(INT_MAX, '\n');
	
	q1.set_x(x);
	q1.mult(x*x);
	
	cout<<"q1.x^3 = "<<q1.get_x()<<endl;

	quad q2(x); q2.mult(x);
	std::cout<<"q1.x^2 = "<<q2.get_x()<<endl;
	q1 = q2;
	cin.get();
}

/*
Konstruktor, x = 0
x = 3
q1.x^3 = 27
Konstruktor, x = 3
q1.x^2 = 9
*/