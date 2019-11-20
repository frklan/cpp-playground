#pragma once

#include "curses_lib/Application.h"
#include "curses_lib/Panel.h"

namespace y44::ctimer {
  constexpr int KEY_ESC = 27;
  constexpr int KEY_Q = 113;

  class Application : public y44::curses_lib::Application {
    public:
      Application();
      bool on_key(int key_code) override;

    private:
      std::unique_ptr<y44::curses_lib::Panel> p;
  };
} // namespace y44::ctimer
