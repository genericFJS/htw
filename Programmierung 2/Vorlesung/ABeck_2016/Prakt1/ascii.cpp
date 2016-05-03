#include <iostream>
#include <iomanip>
#include <ctype.h>

using namespace std;

class ascii{
public:
	ascii(){ cout<<"ASCII-Code von 0 bis 127"<<endl; }

	void out(){
		cout<<'\n'<<endl;
		for (int i=0; i<4; i++) cout<<"| dec hex char ";
		cout<<'|';
		for(int i=0; i<128/4; i++)
		{
			cout<<'\n'<<"| ";
			for(int j=i; j<128; j += 128/4)
			{
				cout<<setw(4)<<dec<<j<<setw(3)<<hex<<j;
				if (isgraph(j)) cout<<setw(4)<<char(j)<<"  | ";
				else cout<<"   .  | ";  	  
			}
		}
	}
};

void main()
{
 ascii a;
 a.out();
 cin.get();
}

/*

| dec hex char | dec hex char | dec hex char | dec hex char |

|    0  0   .  |   32 20   .  |   64 40   @  |   96 60   `  |
|    1  1   .  |   33 21   !  |   65 41   A  |   97 61   a  |
|    2  2   .  |   34 22   "  |   66 42   B  |   98 62   b  |
|    3  3   .  |   35 23   #  |   67 43   C  |   99 63   c  |
|    4  4   .  |   36 24   $  |   68 44   D  |  100 64   d  |
|    5  5   .  |   37 25   %  |   69 45   E  |  101 65   e  |
|    6  6   .  |   38 26   &  |   70 46   F  |  102 66   f  |
|    7  7   .  |   39 27   '  |   71 47   G  |  103 67   g  |
|    8  8   .  |   40 28   (  |   72 48   H  |  104 68   h  |
|    9  9   .  |   41 29   )  |   73 49   I  |  105 69   i  |
|   10  a   .  |   42 2a   *  |   74 4a   J  |  106 6a   j  |
|   11  b   .  |   43 2b   +  |   75 4b   K  |  107 6b   k  |
|   12  c   .  |   44 2c   ,  |   76 4c   L  |  108 6c   l  |
|   13  d   .  |   45 2d   -  |   77 4d   M  |  109 6d   m  |
|   14  e   .  |   46 2e   .  |   78 4e   N  |  110 6e   n  |
|   15  f   .  |   47 2f   /  |   79 4f   O  |  111 6f   o  |
|   16 10   .  |   48 30   0  |   80 50   P  |  112 70   p  |
|   17 11   .  |   49 31   1  |   81 51   Q  |  113 71   q  |
|   18 12   .  |   50 32   2  |   82 52   R  |  114 72   r  |
|   19 13   .  |   51 33   3  |   83 53   S  |  115 73   s  |
|   20 14   .  |   52 34   4  |   84 54   T  |  116 74   t  |
|   21 15   .  |   53 35   5  |   85 55   U  |  117 75   u  |
|   22 16   .  |   54 36   6  |   86 56   V  |  118 76   v  |
|   23 17   .  |   55 37   7  |   87 57   W  |  119 77   w  |
|   24 18   .  |   56 38   8  |   88 58   X  |  120 78   x  |
|   25 19   .  |   57 39   9  |   89 59   Y  |  121 79   y  |
|   26 1a   .  |   58 3a   :  |   90 5a   Z  |  122 7a   z  |
|   27 1b   .  |   59 3b   ;  |   91 5b   [  |  123 7b   {  |
|   28 1c   .  |   60 3c   <  |   92 5c   \  |  124 7c   |  |
|   29 1d   .  |   61 3d   =  |   93 5d   ]  |  125 7d   }  |
|   30 1e   .  |   62 3e   >  |   94 5e   ^  |  126 7e   ~  |
|   31 1f   .  |   63 3f   ?  |   95 5f   _  |  127 7f   .  |
*/
