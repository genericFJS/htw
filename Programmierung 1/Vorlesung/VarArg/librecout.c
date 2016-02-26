// gcc -c librecout.c
// ar rvs librecout.a librecout.c
// sudo cp librecout.a /usr/local/librecout.a
// sudo cp recout.h /usr/local/include

#include "recout.h"



void myputc(char c)
{
    asm("mov $4,%eax");
    asm("mov $1,%ebx");
    asm("lea 8(%ebp),%ecx");
    asm("mov $1,%edx");
    asm("int $0x80");
}

void mydputc(int fdescr, char c)
{
    asm("mov $4,%eax");
    asm("mov 8(%ebp),%ebx");
    asm("lea 12(%ebp),%ecx");
    asm("mov $1,%edx");
    asm("int $0x80");
}

void myfputs(char *c,int fdescr, int len)
{
    asm("mov $4,%eax");
    asm("mov 12(%ebp),%ebx");
    asm("mov 8 (%ebp),%ecx");
    asm("mov 16(%ebp),%edx");
    asm("int $0x80");
}

void myputs(char* p)
{
  if(*p)
  {
    myputc(*p);
    myputs(++p);
  }
}

void myuputd(unsigned int n)
{
  if (n/10) myuputd(n/10);
  myputc(n%10+'0');
}

void myputd(long d)
{
  char m='-';
  if (d<0) {myputc(m);d=-d;}
  myuputd((unsigned)d);
}

void myputx(unsigned long d)
{
  if (d>=0x10) myputx(d/0x10);
  myputc(d%0x10>9?d%16+'A'-10:d%16+'0');
}

void myputsnl(char *s )
{
  myputs( s );
  myputs( "\n" );
}

int mystrlenr(char*p,int n)
{
  if(*p)n=mystrlenr(p+1,n+1); 
  return n;
}

int mystrlen(char*p)
{
  mystrlenr(p,0);
}

int myuatoi(char* p,unsigned i)
{
  if(*p)
  {
    i=i*10+(*p -'0');
    i=myuatoi(p+1,i);
  }
  return i;
}

char* eatws(char*p)
{
  if(*p==' '|| *p=='\t')p=eatws(p+1);
  return p;
}

int myatoi(char* p)
{
  char m=0;
  int i=0;
  //while(*p==' ')p++;
  p=eatws(p);
  if(*p=='-'){p++;m=1;}
  //while(*p)i=i*10+(*p++ -'0');
  i=myuatoi(p,(unsigned)i);
  if(m) i-=i;
  return i;
}

void mydputs(char *c,int fdescr, int len)
{
    asm("mov $4,%eax");
    asm("mov 12(%ebp),%ebx");
    asm("mov 8 (%ebp),%ecx");
    asm("mov 16(%ebp),%edx");
    asm("int $0x80");
}
/*
void myputs(char* p)
{
  while(*p)myputc(*p++);
}*/

void myputdouble(double d)
{
  int i;
  if(d<0){myputc('-');d=-d;}
  i=d;
  myuputd(i);myputc('.');
  d-=i;
  d*=1000;
  i=d;
  if (i<10)  {myputs("00"); myuputd(i);} else
  if (i<100) {myputs("0");  myuputd(i);} else
                            myuputd(i);
}