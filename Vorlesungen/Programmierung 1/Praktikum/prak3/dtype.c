#include <stdio.h>
#include <stdlib.h>

char vBuf[128];

int main(){
	signed char		my_sc;
	unsigned char	my_uc;
	signed short	my_ss;
	unsigned short	my_us;
	signed int		my_si;
	unsigned int	my_ui;
	signed long		my_sl;
	unsigned long	my_ul;
	
	float			my_fl;
	double			my_db;
	
   printf("enter signed char: ");
	fgets(vBuf,128,stdin); my_sc=atoi(vBuf);
   printf("enter unsigned char: ");
	fgets(vBuf,128,stdin); my_uc=atoi(vBuf);
   printf("enter signed short: ");
	fgets(vBuf,128,stdin); my_ss=atoi(vBuf);
   printf("enter unsigned short: ");
	fgets(vBuf,128,stdin); my_us=atoi(vBuf);
   printf("enter signed int: ");
	fgets(vBuf,128,stdin); my_si=atoi(vBuf);
   printf("enter unsinged int: ");
	fgets(vBuf,128,stdin); my_ui=atoi(vBuf);
   printf("enter signed long: ");
	fgets(vBuf,128,stdin); my_sl=atoi(vBuf);
   printf("enter unsigned long: ");
	fgets(vBuf,128,stdin); my_ul=atoi(vBuf);
	
	//fgets(vBuf,128,stdin); my_fl=atoi(vBuf);
	//fgets(vBuf,128,stdin); my_db=atoi(vBuf);
	
	printf("type                     address  deci hex\n");
   printf("signed		char	%p %d %X\n",&my_sc, my_sc, my_sc);
	printf("unsinged	char	%p %d %X\n",&my_uc, my_uc, my_uc);
	printf("signed		short	%p %d %X\n",&my_ss, my_ss, my_ss);
	printf("unsinged	short	%p %d %X\n",&my_us, my_us, my_us);
	printf("signed		int	%p %d %X\n",&my_si, my_si, my_si);
	printf("unsinged	int	%p %d %X\n",&my_ui, my_ui, my_ui);
	printf("signed		long	%p %d %X\n",&my_sl, my_sl, my_sl);
	printf("unsinged	long	%p %d %X\n",&my_ul, my_ul, my_ul);
	
	//printf("float				%p %d %X\n",&my_fl, my_fl, my_fl);
	//printf("double				%p %d %X\n",&my_db, my_db, my_db);
	
	return 0;
}
