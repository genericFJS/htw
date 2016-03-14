// Klassen mit Pointermember

class myStr
{
  char * pStr;
  int length;
  public:
  myStr(const char* pstr);
  myStr();
  myStr(char x, int n);
  void setChar(int idx, char x);
  int  getChar(int idx)const;
  void display()const;
  ~myStr(){delete[] pStr;}
};