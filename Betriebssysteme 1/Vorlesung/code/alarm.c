#include <stdio.h>
#include <unistd.h>
#include <curses.h>

#define PAUSE 300000
#define SECONDS 10
int main(void)
{
  long ret;

  /* we give us some seconds to run */
  ret = alarm(SECONDS);
 
  initscr();
  cbreak();
  while(1) {
    mvprintw(0,0, "oOOo");
    refresh();
    usleep(PAUSE);
    mvprintw(0, 0, "OooO");
    refresh();
    usleep(PAUSE);
  }
  

}
