
#include "MainWindow.h"

#include <chrono>
#include <iostream>
#include <libredeo/intervall.h>
#include <ncursesw/cursesp.h>
#include <ncursesw/cursesw.h>
#include <thread>

using namespace std::chrono_literals;

MainWindow::MainWindow() {
  std::clog << "MainWindow::MainWindow()\n";

  curs_set(0);
  start_color();
  nodelay(true);

  //height, width, y, x
  titlebarWin = std::make_unique<NCursesPanel>(5, this->cols() - 2, 0, 1);
  
  // left, right, top, bottom, 
  // top-left, top-right, bottom-left, bottom-right
  // ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
  // ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER
  titlebarWin->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
                    ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  titlebarWin->printw(0, 3, " Hello World! ");
  
  logWin = std::make_unique<NCursesPanel>(this->lines() - 6, this->cols() / 2 - 2, 6 , 1);
  logWin->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
                    ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  logWin->printw(0, 3, " Log ");
  logWin->printw(1, 1, "Log created!");

  timerWin = std::make_unique<NCursesPanel>(this->lines() - 6, this->cols() / 2, 6, this->cols() / 2 - 1);
  timerWin->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
                    ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  timerWin->printw(0, 3, " Timer ");

  yellowfortyfourcom::IntervallTimer::make_intervall(3s, [&](){ 
      static uint8_t line = 2;
      logWin->printw(line++, 1, "timer event (%d)", count++);
      logWin->refresh();
    }, 60);
}

int MainWindow::run() {
  
  refresh();
  bool quit = false;
  while(!quit){
    int c = getch();

    switch(c) {
      case 'q': {
        quit = true;
        break;
      } case 'h':{
        titlebarWin->hide();
        break;
      } case 's': {
        titlebarWin->show();
        titlebarWin->refresh();
        break;
      } default: {
      }
    }

    std::this_thread::sleep_for(3ms); // dont hog cpu!
  }

  return 0;
}

MainWindow::~MainWindow()
{
  yellowfortyfourcom::IntervallTimer::cancel_all_timers(); 
  endwin();
}

