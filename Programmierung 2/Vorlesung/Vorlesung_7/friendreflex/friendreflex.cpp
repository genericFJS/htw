#include <iostream>

using namespace std;

class y;
class x;

class x {
	friend class y;
		void outx(){ cout<<"out x\n"; }
	public:
	//	void call_outy(y &y1){ y1.outy(); }
};

class y {
	friend class x;
		void outy(){ cout<<"out y\n"; }
	public:
		void call_outx(x &x1){ x1.outx(); }
};

void main(){
	x x1;
	y y1;
//	x1.call_outy(y1);
	y1.call_outx(x1);
	cin.get();
}

/*
out x
*/