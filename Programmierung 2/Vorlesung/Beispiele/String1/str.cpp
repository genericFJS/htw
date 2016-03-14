#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#include "str.h"



myStr::myStr(const char* pstr)
{
  this->length=strlen(pstr);
  this->pStr=new char[length+1];
  strcpy(this->pStr,pstr);
}

myStr::myStr()
{
  length=0; pStr=new char;
  *pStr=0;
}

myStr::myStr(char x, int n)
{
  this->length=n;
  this->pStr=new char[length+1];
  memset(this->pStr, x, n);
}
void myStr::setChar(int idx, char x)
{
  if (idx<length)pStr[idx]=x;
}

int  myStr::getChar(int idx)const
{
  if (idx<length)return pStr[idx];
  else return -1;
}

void myStr::display()const
{
  cout<<pStr;
}