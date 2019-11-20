#pragma once

#include "Panel.h"

#include <map>
#include <memory>
#include <ncursesw/cursesp.h>
#include <vector>

namespace y44::curses_lib {
  class Application {
    public:
      Application();
      virtual ~Application();

      virtual void operator()() final;
      virtual bool on_init() { return false; }
      virtual bool on_quit() { return false; }
      virtual bool on_key(int /*key_code**/) { return false;} 
      // std::shared_ptr<y44::curses_lib::Panel> add_child_view(const std::string name, std::shared_ptr<Panel> view) {}

      Size get_screen_size() const;
      void quit() { m_quit = true; }

    private:
      std::unique_ptr<NCursesPanel> m_mainview;
      std::shared_ptr<Panel> m_activeView;
      std::map<std::string, std::shared_ptr<Panel>> m_views;
      bool m_quit = false;
  };

} // namepsace y44:curses_lib

