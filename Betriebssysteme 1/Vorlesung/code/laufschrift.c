/*
   laufschrift.c

   simples curses-Beispiel
   - gcc -o laufschrift laufschrift.c -lcurses
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>

char text[] = {"Linux ist das beste Betriebssystem der Welt."};

int main(void)
{
  unsigned int x=0, y=0;

  initscr();                           /* Initialisiert das Terminal     */
  cbreak();                            /* Zeichen sofort weiterreichen   */
  noecho();                            /* Kein Echo bei getch()          */
  nodelay(stdscr, TRUE);      /* nicht blockierender Aufruf von getch()  */

  do {
    clear();
    mvprintw(x, y, "%s", text);
    refresh();
    y++;
    if (y>=80) {
      x++;
      y=0;
    }
    if (x>=80) {
      x=0;
      y=0;
    }
    usleep(100000);
  }
  while (getch() == ERR);
  endwin();
  exit(EXIT_SUCCESS);
}

