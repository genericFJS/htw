#include <iostream>
using namespace std;

class integer { // int - Variable in class verpacken
//	private:    // private ist default
		int i;  // this->i bzw. (*this).i
	public: 
		integer(int i=0):i(i){  // Konstruktor und Defaultkonstruktor
			// i=0 default Wert, wenn keiner Angeben
			// :i(i) übergebenes i wird dem i der Klasse zugewiesen: i(i_1) i ist this->i, und i_1 ist das übergebene 
			cout<<"integer-Objekt i = "<<this->i<<endl; 
		}

		int get(){ return i; }

		void set(int i=0){ this->i = i; }

		static integer add(integer i1, integer i2){  // Wertkopien von i1 und i2
		// return integer(i1.i + i2.i); // alternativ und explizit: Konstruktor-Aufruf
		   return i1.get()+i2.get();    // Umwandlung int nach integer, Aufruf Konstruktor implizit
		}
};

auto max(int x, int y) -> int { return x>y ? x : y; }

template<typename Typ1, typename Typ2>
auto quotient(Typ1 a, Typ2 b) -> decltype(a/b) { return a/b; }

auto main() -> int {
	auto k = 0;        // C++11: da 0 vom Typ int ist auch k vom Typ int
	decltype(k) j = 5; // C++11: da k vom Typ int ist auch j vom Typ int
	char *c = nullptr; //C++ 11: Zeigerliteral
	int *ip = NULL;

	integer i0(5), i1=4;     // 2 (alternative) Initialisiierungen von Objekten
	cout<<"i0.i = "<<i0.get()<<endl;
	cout<<"i0.i + i0.i = "<<integer::add(i0, i0).get()<<endl; // Aufruf static-Methode add
	integer i3 = integer::add(i0, i0);                        // Initialisierung von i3
	cout<<"i3.i     = "<<i3.get()<<endl;
	i0.set(22);
	cout<<"i0.i     = "<<i0.get()<<endl;
	cout<<"max(3,5) = "<<max(3,5)<<endl;
	cout<<"5/3      = "<<quotient(5, 3)<<endl;
	cout<<"5.0/3.0  = "<<quotient(5.0, 3.0)<<endl;
	cout<<"b / 1    = "<<quotient('b', '1')<<endl;
	cin.get();
}

/*
integer-Objekt i = 5
integer-Objekt i = 4
i0.i = 5
integer-Objekt i = 10
i0.i + i0.i = 10
integer-Objekt i = 10
i3.i     = 10
i0.i     = 22
max(3,5) = 5
5/3      = 1
5.0/3.0  = 1.66667
*/
