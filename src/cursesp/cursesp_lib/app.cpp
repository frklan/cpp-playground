#include "app.h"

#include <libredeo/intervall.h>
#include <iostream>
#include <ncursesw/cursesapp.h>
#include <ncursesw/cursesw.h>
#include <ncursesw/cursesp.h>
#include <memory>
#include <version.h>

using namespace std::chrono_literals;

App::App() : NCursesApplication(false) {
  std::clog << "\n\nApp::App()\n";
  std::clog << "--- testing native c++ wrapper for curses ---\n";
  std::clog << version();
  }

App::~App()
{
  yellowfortyfourcom::IntervallTimer::cancel_all_timers();
  endwin();
}

int App::run() {
  curs_set(0);
  start_color();
  Root_Window->nodelay(true);

  //height, width, y, x
  titlebarWin = std::make_unique<NCursesPanel>(5, this->Root_Window->cols() - 2, 0, 1);
  
  // left, right, top, bottom, 
  // top-left, top-right, bottom-left, bottom-right
  // ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
  // ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER
  titlebarWin->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
                    ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  titlebarWin->printw(0, 3, " Hello World! ");
  titlebarWin->refresh();
  
  logWin = std::make_unique<NCursesPanel>(this->Root_Window->lines() - 6, this->Root_Window->cols() / 2 - 2, 6 , 1);
  logWin->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
                    ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  logWin->printw(0, 3, " Log ");
  logWin->printw(1, 1, "Log created!");
  logWin->refresh();

  timerWin = std::make_unique<NCursesPanel>(this->Root_Window->lines() - 6, 
    this->Root_Window->cols() / 2, 6, this->Root_Window->cols() / 2 - 1);
  timerWin->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
                    ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  timerWin->printw(0, 3, " Timer ");
  timerWin->refresh();

  yellowfortyfourcom::IntervallTimer::make_intervall(3s, [&]() {
    static uint8_t line = 2;
    logWin->printw(line++, 1, "timer event (%d)", count++);
    logWin->refresh();
  }, 60);
  
  return loop();
}

int App::loop() {
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
