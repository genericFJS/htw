//#include "recout.h"

#include <stdarg.h>
#include <recout.h>

void myprintf(char* frmt,...);


int main(int argc, char* argv[])
{
  char * text="error without <numeral> in Commandline\n";
  double dvar=123.4567;
  if(argc!=2) mydputs(text,2,mystrlen(text));
  else
  {
   int i=myatoi(argv[1]);
   myputsnl("start");
   myputd(i);
   myputsnl("");
   myuputd(i);
   myputsnl("");
   myputx(i);
   myputsnl("");
   myputs("hallo\n");
   myprintf("myprintf: dec: %d, Unsigned: %u, Hex: %x, char: %c, double: %f, Text: %s\n",
	     i,i,i,i,dvar, "das war's");
    myprintf("das sind die Zahlen %d, %d char:%c long: %l\n",12,89,'A', 99L);
    myprintf("%s %f\n","Mein Double Wert: ",123.456);
   myputsnl("stop");
  }
  return 0;
}
void myprintf(char* frmt,...)
{
  int ival;
  unsigned uval;
  char cval;
  double dval;
  long lval;
  char *sarg;
  int i;
  
  va_list ap;
  va_start(ap,frmt);
  for (i=0;frmt[i];i++)
  {
    if (frmt[i]=='%')
    switch(frmt[++i])
    {
      case '%': myputc('%');                               break;
      case 'd': ival=va_arg(ap,int);    myputd(ival);      break;
      case 'u': uval=va_arg(ap,unsigned);myuputd(uval);	   break;
      case 'x': uval=va_arg(ap,unsigned);myputx(uval);	   break; 
      case 'c': cval=va_arg(ap,int);    myputc(cval);      break;
      case 'l': lval=va_arg(ap,long);   myputd(lval);      break;     
      case 'f': dval=va_arg(ap,double); 
		myputdouble(dval); break;
      case 's': for (sarg=va_arg(ap,char*); *sarg; sarg++) myputc(*sarg); break;
      default : 		                           break;
    }
    else myputc(frmt[i]);
  }
  va_end(ap);
}
