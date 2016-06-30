const int SizeArr = 24;

class Range{};
template <class T>
class IntArr
{
   public:
      class Range{};

      IntArr (int Gr = SizeArr);		// Konstruktor
      IntArr (const IntArr<T>&);		// Kopierkonstruktor
      ~IntArr() {delete IA;}
      IntArr & operator = (const IntArr<T>&);	// Ueberladener
      T&  operator [] (int i);			// Ueberlad. []-operator
      int   getNum()const {return Size;}	// Uebergabe der Groesse
      void  resize(int NewSz);			// Neue Groesse
   private:
      int   Size;				// Groesse des Feldes
      T * IA;
};

template <class T>
IntArr<T> :: IntArr (int Sz)
{
  Size = Sz;
  IA = new T [Size];
  for (int i=0; i<Sz; ++i) IA[i]=0;
}

template <class T>
IntArr<T> :: IntArr (const IntArr<T>& Other)
{
  Size = Other.Size;
  IA = new T[Size];
  for (int i=0; i<Size;++i) IA[i]=Other.IA[i];
}

template <class T>
IntArr<T>& IntArr<T> :: operator = (const IntArr<T>& Other)
{
  delete IA;
  IA = new T [Other.Size];
  Size = Other.Size; 
  for ( int i=0; i<Size;i++) IA[i]=Other.IA[i];
  return * this;
}

template <class T>
T& IntArr<T> :: operator []( int i)
{
  static T Dummy=0;

  if ( i>=0 && i<Size) return IA[i];
  else 
  {
    throw Range();
  }
}

template <class T>
void IntArr<T> :: resize (int NewSz)
{
  T*    OldIA = IA;
  int   OldSz = Size;
  Size = NewSz;
  IA = new T[Size];
  int i;
  for (i=0; i<OldSz; ++i) IA[i]=OldIA[i];
  for (   ; i<Size ; ++i) IA[i]=0;
  delete OldIA;
}


