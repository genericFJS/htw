#include <iostream>

using namespace std;

class over {
public:
	/*static int divide(int x, int y, int &Rest) {
		Rest = x % y;
		return x / y;
	}*/

	static double divide(int x, int y) {
		return (double)x / y;
	}

	static int divide(const int &x, const int &y, int &Rest) {
		Rest = x % y;
		return x / y;
	}
};

int main() {
	int rest = 0, quot = 0, x = 10, y = 3;

//	quot = over::divide(10, 3, rest);

	quot = over::divide(x, y, rest);
	cout << "x = " << x << "  y = " << y
		<< "\nx / y = " << quot 
		<< "\nx % y = " << rest << endl;

	cout << "x / y = " << over::divide(x, y) << endl;

	cin.get();
	return 0;
}

/*
x = 10  y = 3
x / y = 3
x % y = 1
x / y = 3.33333
*/