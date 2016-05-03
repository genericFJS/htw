#include<iostream>

class Objekt {
public:
   virtual ~Objekt() {
      std::cout << "Objekt-Destruktor aufgerufen (" 
                << this << ")" << std::endl;
   }
   static void *operator new(size_t size) {
      std::cout << "new aufgerufen. size=" << size << std::endl;
      return  ::operator new(size);
   }
   static void operator delete(void* ptr, size_t size) {
      std::cout << "delete aufgerufen. size="  << size << std::endl;
      ::operator delete(ptr);
   }
   static void *operator new[](size_t size) {
      std::cout << "new[] aufgerufen. size=" << size << std::endl;
      return  ::operator new[](size);
   }
   static void operator delete[](void* ptr, size_t size) {
      std::cout << "delete[] aufgerufen. size="  << size << std::endl;
      ::operator delete[](ptr);
   }
};