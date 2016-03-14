#include <stdio.h>

#include <ctype.h>

int main()
{

  int	i,j;

  printf("Content-Type: text/html");
  printf("\n\n")  ;
  /*puts("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">");*/
  puts("<html><head><title>CGI-Script - ASCII Codetabelle</title></head>\n");
  puts("<body><h2><hr>\n");
  puts("<pre>\n");

  for (i=0; i<4; i++)printf("|dec hex Char ");
  printf("|\n");
  for (i=0; i<32; i ++)
  {              
    printf("\n| ");
    for (j=0; j < 128; j += 128/4)
    {
      printf("%3d %2X ",i+j,i+j);
      if (isgraph(j+i))printf("  %c  | ",j+i);
      else printf("  .  | ");
    }
  }
  puts("</pre><hr>");
  puts("<a href=\"http://www.informatik.htw-dresden.de/~beck/a.beck.html\">A. Beck</A> <p>");
  puts("</body>\n");
  puts("</html>\n");
  return 0;
}

