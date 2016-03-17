#include <iostream>         //cla1.cpp

using namespace std;

class foo{
   public:
	   class bar{             //static
		 public: static char *c;
				 size_t w;
	 } b;                     //b nicht static

     enum farbe {red, blue, green }; //static
     typedef farbe rgb;              //static
	 static rgb get_color(){ return color; }
	 static void set_color(rgb c){ color=c; }
	 static size_t get_rgb_n(){ return rgb_n; }
   private:
	 static size_t rgb_n;     //Anzahl in rgb
	 static rgb color;
};

size_t foo::rgb_n=3;		  //Initialisierung
foo::rgb foo::color=foo::blue; 

char *foo::bar::c="TU Dresden";

void main(){
	cout<<"foo::rgb_n  = "<<foo::get_rgb_n()
		<<'\n';
	for(size_t i=0; i<foo::get_rgb_n(); i++){
		foo::set_color(foo::rgb(i));
		cout<<"foo::color  = "
			<<foo::get_color()<<'\n';
	}

    foo::bar::c="HTW Dresden";
	cout<<"foo::bar::c = "<<foo::bar::c<<endl;
	
	foo f; f.b.w=5;
    cout<<"f.b.w       = "<<f.b.w<<endl;
	cin.get();
}

/*
foo::rgb_n  = 3
foo::color  = 0
foo::color  = 1
foo::color  = 2
foo::bar::c = HTW Dresden
f.b.w       = 5
*/