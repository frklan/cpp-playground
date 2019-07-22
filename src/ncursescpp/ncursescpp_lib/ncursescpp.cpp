
#include "ncursescpp.h"

#include <iostream>
#include <ncursescpp/Ncurses.hpp>
#include <ncursescpp/ncursescpp.hpp>
#include <string>

constexpr uint8_t MARGIN = 1;

int Ncursescpp::run() {
  std::cout << "ncursescpp::Run() - initing ncurses\n";
 

  nccpp::ncurses().echo(false);
  nccpp::ncurses().cbreak(true);

  height = nccpp::ncurses().line_count();
  width = nccpp::ncurses().column_count();
  
  auto w1 = nccpp::ncurses().add_subwindow(height - MARGIN, width / 2 - MARGIN, 1, 1);
  nccpp::ncurses().get_subwindow(w1).box(nccpp::attributes::normal, nccpp::attributes::normal);

  historyWindow = nccpp::ncurses().add_subwindow(height - MARGIN, width / 2 - MARGIN, 1, width / 2);
  nccpp::ncurses().get_subwindow(historyWindow).box(nccpp::attributes::normal, nccpp::attributes::normal);
  nccpp::ncurses().get_subwindow(historyWindow).mvprintw(0, 2, "History");

  nccpp::ncurses().refresh();

  
  std::string cmd;
  int c;
  do {
    c = nccpp::ncurses().get_subwindow(historyWindow).getch();
    if(c >= ' ' && c <= '~') {
      cmd += static_cast<char>(c);
    } else if(c == '\n') {
      if(!cmd.empty()) {
        addHistory(cmd);
        cmd.clear();
      }
    }
  } while(c != nccpp::keys::backspace);

  return 0;
}

void Ncursescpp::addHistory(const std::string& entry) {
 
  //nccpp::ncurses().get_subwindow(historyWindow).

  history.push_back(entry);

  size_t startPos = 0; 
  if(history.size() > static_cast<size_t>(height) - 2) {
    startPos = history.size() - static_cast<size_t>(height) + 2;
  } else {
    startPos = 0;
  }

  //printw("%d\n", startPos);
  //nccpp::ncurses().get_subwindow(historyWindow).clear();
  auto& hist = nccpp::ncurses().get_subwindow(historyWindow);
  hist.redraw();
  
  uint16_t row = 1;
  for(auto i = startPos; i < history.size(); i++) {
  //nccpp::ncurses().printw("%s", history.at(i).c_str());    
  nccpp::ncurses().get_subwindow(historyWindow).mvprintw(row, 1, "%s", history.at(i).c_str());
    row++;
  }

  nccpp::ncurses().get_subwindow(historyWindow).refresh();
}

