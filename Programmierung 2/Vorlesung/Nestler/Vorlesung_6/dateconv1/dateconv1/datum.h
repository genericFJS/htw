#include <string>

class Datum {
  public:
    Datum();                         // Default-Konstruktor
    void aktuell();                  // Systemdatum setzen
   
    // besser: durch Methode string toString() ersetzen!
    operator std::string() const;     // Typumwandlungsoperator
  private:
    int tag_, monat_, jahr_;
};
