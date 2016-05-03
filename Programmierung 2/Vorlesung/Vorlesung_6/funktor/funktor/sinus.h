#include <cmath>   //  sin(), Konstante M_PI für pi
#ifndef M_PI
 #define M_PI 3.14159265358979323846
#endif

class Sinus {
    public:
      enum Modus { bogenmass, grad, neugrad };
      Sinus(Modus m = bogenmass): berechnungsart(m) {}

      double operator()(double arg) const {
         double erg = 0.0;
         switch(berechnungsart) {
			 case bogenmass : erg = std::sin(arg);            break;
			 case grad      : erg = std::sin(arg/180.0*M_PI); break;
			 case neugrad   : erg = std::sin(arg/200.0*M_PI); break;
			 default   : ; 
         }
         return erg;
      }
    private:
	  Modus berechnungsart;
};