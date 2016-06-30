#include "Person.h"
using namespace std;

int main() {
   Person person("Lena");                // Stack-Objekt
   cout << "Name : " << person.getName() << endl;
   Person* ptr1 = new Person("Jens");    // Heap-Objekt
   cout << "Name : " << ptr1->getName() << endl;
   delete ptr1;              // Löschen des Heap-Objekts

   size_t anz = 2;
   Person* arr = new Person[anz];   // dynamisches Array anlegen
   for(size_t i = 0; i < anz; ++i) {
      cout << i << ": " << arr[i].getName() << endl;
   }
   delete[] arr;                 // dynamisches Array löschen
   cin.get();
}

/*
Name : Lena
new aufgerufen. size=36
Name : Jens
Person-Destruktor aufgerufen (Jens)
Objekt-Destruktor aufgerufen (00345CE8)
delete aufgerufen. size=36
new[] aufgerufen. size=76
0: HTW
1: HTW
Person-Destruktor aufgerufen (HTW)
Objekt-Destruktor aufgerufen (00345D10)
Person-Destruktor aufgerufen (HTW)
Objekt-Destruktor aufgerufen (00345CEC)
delete[] aufgerufen. size=36
Person-Destruktor aufgerufen (Lena)
Objekt-Destruktor aufgerufen (0012FF30)
Drücken Sie eine beliebige Taste . . .
*/