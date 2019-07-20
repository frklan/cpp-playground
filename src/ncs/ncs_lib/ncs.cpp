#include "ncs.h"

#include <cmath>
#include <curses.h>
#include <iostream>
#include <string>

constexpr int KEY_ESC = 27;

int Ncs::run() {
  std::cout << "Ncs::Run() - initing ncurses\n";
  
  initscr();
  if(has_colors()) {
    start_color();
  }
  
  if(LINES < 10 || COLS < 10) {
    std::cout << "Screen to small\n";
    return -1;
  }

  cbreak();
  noecho();
  nonl();
  intrflush(nullptr, FALSE);
  keypad(stdscr, TRUE);
  curs_set(0);
  refresh();

  createWindows();

  int c;
  std::string cmd;
  do {
    c = getch();
    
    if(c >= ' ' && c < 127) {
      cmd += static_cast<char>(c);
    } else if(c == '\r') {
      if(!cmd.empty()) {
        addHistory(cmd);
        cmd.clear();
        refresh();
      }
    } else if(c == KEY_RESIZE) {
      destroyWindows();
      createWindows();
    }
  } while(c != KEY_ESC);
  
  clear();
  destroyWindows();
  endwin();

  return 0;
}

void Ncs::createWindows() {
  screen_win = newwin(0,0,0,0);
  wrefresh(screen_win);
  
  history_size.height = static_cast<size_t>(LINES - 5);
  history_size.width = static_cast<size_t>(std::floor(COLS / 2));

  history_win = newwin(static_cast<int>(history_size.height), static_cast<int>(history_size.width), 1, static_cast<int>(std::floor(COLS / 2)));
	box(history_win, 0, 0);
  mvwprintw(history_win, 0, 5, "  History  ");
  wrefresh(history_win);

  command_win = newwin(3, COLS - 1, LINES - 3, 1);
  box(command_win, 0, 0);
  
  wrefresh(command_win);
}

void Ncs::destroyWindows() {
  delwin(command_win);
  command_win = nullptr;

  delwin(history_win);
  history_win = nullptr;

  delwin(screen_win);
  screen_win = nullptr;

  clear();
  refresh();
}
void Ncs::addHistory(const std::string& entry) {
  history.push_back(entry);

  size_t startPos = 0; 
  if(history.size() > history_size.height - 2) {
    startPos = history.size() - history_size.height + 2;
  } else {
    startPos = 0;
  }

  //printw("%d\n", startPos);
  redrawwin(history_win);
  
  uint16_t row = 1;
  for(auto i = startPos; i < history.size(); i++) {
    
    mvwprintw(history_win, row, 1, "%s", history.at(i).c_str());
    row++;
  }

  wrefresh(history_win);

}
