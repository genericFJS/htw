#include <iostream>
using namespace std;

class musiker { public: void greet(); // non-virtual
			virtual void play();      // virtual
};

void musiker::greet(){ cout<<"Musiker sagt: hello\n"; }
void musiker::play(){  cout<<"Musiker spielt: mmmm mmmm\n"; }

class trompeter : public musiker { public:
				    void greet(); // override non-virtual
				    void play();  // override virtual
				 };

void trompeter::greet(){ 
	cout<<"Trompeter sagt: Was ist los ?\n"; 
}

void trompeter::play(){ 
	cout<<"Trompeter spielt: toot toot\n";
}

void func(musiker &rm){ rm.play(); } //ruft virtuelle Fkt.

void main(){ trompeter t; musiker m, *pm;

  //1.: Aufruf ueber Instanz der Klasse musiker
  m.greet();    // Musiker sagt: hello\n
  m.play();     // Musiker spielt: mmmm mmmm

  //2.: Aufruf ueber Instanz der Klasse trompeter
  t.greet();    // Trompeter sagt: Was ist los ?
  t.play();     // Trompeter spielt: toot toot

  //3.: Aufruf ueber musiker's Zeiger auf musiker-Instanz
  pm=&m;        // Zeigt auf musiker
  pm->greet();  // Musiker sagt: hello\n
  pm->play();   // Musiker spielt: mmmm mmmm

  //4.: Aufruf ueber musiker's Zeiger auf trompeter-Instanz
  pm=&t;        // Zeigt auf trompeter
  pm->greet();  // Musiker sagt: hello\n
  pm->play();   // Trompeter spielt: toot toot
  pm->musiker::play(); // Musiker spielt: mmmm mmmm

  //Aufruf ueber Referenz
  func(m);      // musiker::play()
  func(t);      // trompeter::play()
  cin.get();
}

/*
Musiker sagt: hello
Musiker spielt: mmmm mmmm
Trompeter sagt: Was ist los ?
Trompeter spielt: toot toot
Musiker sagt: hello
Musiker spielt: mmmm mmmm
Musiker sagt: hello
Trompeter spielt: toot toot
Musiker spielt: mmmm mmmm
Musiker spielt: mmmm mmmm
Trompeter spielt: toot toot
*/