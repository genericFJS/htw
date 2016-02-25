
// Strukturtyp struct tStudent
// darin die Komponeneten: name, matrNr, klNote und belNote
typedef unsigned int uint;

typedef 
struct// tStudent
{
  char* name;
  uint  matrNr;
  int   belNote;
  float klNote;
}tStud;

void putStud(tStud s);
void putStudp(tStud* s);
tStud getStud2();