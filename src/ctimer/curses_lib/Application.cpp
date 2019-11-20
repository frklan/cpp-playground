#include "Application.h"
#include "Panel.h"
#include <chrono>
#include <iostream>
#include <thread>

namespace y44::curses_lib {
  Application::Application() {
    auto* win = ::initscr();
    ::cbreak();
    ::noecho();
    ::curs_set(0);
    ::start_color();
    ::nodelay(win, true);
    ::clear();
    
    m_mainview = std::make_unique<NCursesPanel>();
    m_mainview->refresh();
  }

  Application::~Application() {
    ::endwin();
  }

  void Application::operator()() {
    std::clog << "curses_lib::Application::operator()()\n";
    on_init();

    do {
      if(auto key_code = m_mainview->getch(); key_code > 0) {
        if(!on_key(key_code)) {
          m_activeView->on_key(key_code);
        }
        std::clog << "done keys\n";
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    } while(!m_quit); 
    
    on_quit();
  }

  Size Application::get_screen_size() const {
    auto height = m_mainview->lines();
    auto width = m_mainview->cols();
    return {width, height};
  }

} // namespace y44::curses_lib
