#include <iostream>

using namespace std;

class Rechteck {
	unsigned int laenge, breite;
	double x, y;                  // Position in x-y-Koordinaten
public:
	Rechteck(unsigned int laenge = 0U, unsigned int breite = 0U, 
		     double x = 0.0, double y = 0.0) :laenge(laenge), 
		     breite(breite), x(x), y(y) {
                   cout << "\nRechteck initialisiert"
			<< "\nlaenge = " << this->laenge
			<< "\nbreite = " << this->breite
			<< "\nx      = " << this->x
			<< "\ny      = " << this->y << endl;
	}

	unsigned int get_A() { return laenge * breite; }

	void set_laenge(unsigned int laenge = 0U) { this->laenge = laenge; }

	void set_breite(unsigned int breite = 0U) { this->breite = breite; }

	void set_x(double x = 0.0) { this->x = x; }

	void set_y(double y = 0.0) { this->y = y; }

	void out() {
		cout << "\n";
		for (unsigned int i = 0U; i < laenge; i++) {
			cout << "\n";
			for (unsigned int j = 0U; j < breite; j++)
				cout << 'O';
		}
		cout << "\n\nRechteck " << laenge << "x" << breite << endl;
	}
};

int main() {
	Rechteck r(4U, 9U);
	r.out();
	cin.get();
}

/*
Rechteck initialisiert
laenge = 4
breite = 9
x      = 0
y      = 0


OOOOOOOOO
OOOOOOOOO
OOOOOOOOO
OOOOOOOOO

Rechteck 4x9
*/