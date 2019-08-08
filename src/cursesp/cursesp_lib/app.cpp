#include "app.h"

#include <iostream>
#include <libredeo/intervall.h>
#include <ncursesw/cursesapp.h>
#include <ncursesw/cursesw.h>
#include <ncursesw/cursesp.h>
#include <memory>
#include <sstream>
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
  logWin->nodelay(true);
  logWin->printw(0, 3, " Log ");
  logWin->printw(1, 1, "Log created!");
  logWin->refresh();

  titlebarWin = std::make_unique<NCursesPanel>(5, this->Root_Window->cols() - 2, 0, 1);
  titlebarWin->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, 
      ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  
  //height, width, y, x
  timerWin = std::make_unique<NCursesPanel>(this->Root_Window->lines() / 2 - 6, 
      this->Root_Window->cols() / 4, 6, this->Root_Window->cols() / 2 - 1);
  timerWin->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
                    ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  timerWin->printw(0, 3, " Timer ");
  timerWin->refresh();

  yellowfortyfourcom::IntervallTimer::make_intervall(1s, [&]() {
    std::stringstream msg;
    msg << "Timer event (" << count++ << ")";
    
    auto width = static_cast<int16_t>(timerWin->width());
    auto maxTextLength = static_cast<uint16_t>(width - 2);
    auto ms = msg.str().substr(0, maxTextLength);

    auto len = static_cast<int16_t>(ms.length());
    auto posx = static_cast<int>(width / 2 - len / 2);
    auto posy = static_cast<int>(timerWin->height() / 2);
    
    timerWin->printw(posy, posx, "%s", ms.c_str());
    timerWin->refresh();
  }, 60);
  
  return loop();
}

int App::loop() {
  bool quit = false;
  while(!quit){
    int c = getch();
    if(c != -1) {
      logWin->printw(2, 2, "%c", c);
      std::clog << c << '\n';
    }
    switch(c) {
      case 'q': {
        quit = true;
        break;
      } case 'a':{
        titlebarWin->hide();
        break;
      } case 's': {
        titlebarWin->show();
        titlebarWin->refresh();
        break;
      } case 'h': { //left
        auto x = logWin->begx();
        auto newX = (x > 1 ? --x : x);
        auto y = logWin->begy();

        try {
          logWin->mvwin(y, newX);
        } catch(const std::exception& e) {
          std::cerr << e.what() << '\n';
        }
        logWin->refresh();
        break;
      } case 'j': { // up
        auto x = logWin->begx();
        auto y = logWin->begy();
        auto newY = (y > 1 ? --y : y);

        try {
          logWin->mvwin(newY, x);
        } catch(const std::exception& e) {
          std::cerr << e.what() << '\n';
        }
        logWin->refresh();
        break;
      } case 'k': { // down
        auto screenHeight = logWin->lines();
        
        auto x = logWin->begx();
        auto y = logWin->begy();
        auto winHeight = logWin->height();

        int newY;
        if(y + winHeight < screenHeight) {
          newY = y + 1;
        } else {
          newY = y;
        }

        try {
          logWin->mvwin(newY, x);
        } catch(const NCursesException& e) {
          std::cerr << e.message << '\n';
        }
        logWin->refresh();
        break;
      } case 'l': { // right
        auto screenWidth = logWin->cols();
        auto x = logWin->begx();
        auto y = logWin->begy();
        auto width = logWin->width();

        int newX;
        if(x + width < screenWidth) {
          newX = x + 1;
        } else {
          newX = x;
        }

        try {
          logWin->mvwin(y, newX);
        } catch(const NCursesException& e) {
          std::cerr << e.message << '\n';
        }
        logWin->refresh();
        break;
      } default: {
      }
    }
    std::this_thread::sleep_for(2ms); // dont hog cpu!
  }

  return 0;
}
