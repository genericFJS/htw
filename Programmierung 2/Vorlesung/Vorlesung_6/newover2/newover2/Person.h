
#include <iostream>
#include <string>
#include <cstring>
#include "Objekt.h"

class Person : public Objekt {
public:
   Person(const std::string& n = "HTW") 
      : name(n) {
   }
   ~Person() {
      std::cout << "Person-Destruktor aufgerufen (" 
                << name << ")" << std::endl;
   }
   const std::string& getName() const {
      return name;
   }
private:
   std::string name;
};