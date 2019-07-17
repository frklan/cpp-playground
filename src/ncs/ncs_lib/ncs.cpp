#include "ncs.h"

#include <iostream>
#include <ncurses.h>
#include <string>

int Ncs::run() {

  std::cout << "Ncs::Run() - initing ncurses\n";
  
  initscr();
  if(has_colors()) {
    start_color();
  }
  
  cbreak();
  noecho();
  nonl();
  intrflush(NULL, FALSE);
  keypad(stdscr, TRUE);
  curs_set(0);
  refresh();

  WINDOW* screen = newwin(0,0,0,0);

  WINDOW* history_win = newwin(17, 25, 13, 5);
	box(history_win, 0, 0);

  mvwprintw(history_win, 1, 5, "Fredrik!");
  wrefresh(history_win);

  WINDOW* command = newwin(3, COLS - 1, LINES - 3, 1);
  box(command, 0, 0);
  
  //mvwprintw(command, 1, 2, "Fredrik!");
  wrefresh(command);


  //printw("Hello world!");
  

  char c[] = " ";
  int pos = 2;
  do {
    c[0] = getch();
    //if(c[0] >= 'a' && c[0] <= 'Z') {
      mvwprintw(command, 1, pos, "%c %d", c[0]);
      pos = 2;
      
      
    //}// else if(c[0] == 13) {
     // pos = 2;
      //werase(command);
    //}
    wrefresh(command);
  } while(c[0] != 'q');
  
  clear();
	refresh();
  
  endwin();

  std::cout << "ncurces done!";

  return 0;
}

