#include "Application.h"
#include <thread>

namespace y44::ctimer {
  using namespace std::chrono_literals;
  
  Application::Application() {
    const auto top_view_size = y44::curses_lib::Size{this->get_screen_size().width - 2, 3};

    p = std::make_unique<y44::curses_lib::Panel>(top_view_size, y44::curses_lib::Position{1, 1});
    p->set_labels("Hello", "World!");
    

    constexpr auto short_delay{0.5s};

    constexpr y44::curses_lib::Position p1p{10,5};
    constexpr y44::curses_lib::Size p1s{15, 25};
    auto panel = y44::curses_lib::Panel(p1s, p1p);
    panel.set_labels("A long label that will not fit in the titlebar!", "A shorter bottom label");
    

    std::this_thread::sleep_for(short_delay);

    constexpr y44::curses_lib::Position p2p{25, 15};
    constexpr y44::curses_lib::Size p2s{25, 15};
    auto panel2 = y44::curses_lib::Panel(p2s, p2p);
    panel2.set_labels("Panel #2", "");
    std::this_thread::sleep_for(short_delay);
    panel2.get_label();
    

    constexpr y44::curses_lib::Position p3p{20, 15};
    constexpr y44::curses_lib::Size p3s{25, 15};
    auto panel3 = y44::curses_lib::Panel(p3s, p3p);
    panel3.set_labels("#3 for the win!", "Panel #3");
    std::this_thread::sleep_for(short_delay);
    
    auto [tl, bl] = panel3.get_label();
    std::clog << "top label = '" << tl << "', bottom label = '" << bl << "'\n";
    std::this_thread::sleep_for(short_delay);

    auto panel4 = panel3;
    std::this_thread::sleep_for(short_delay);
    panel4.set_labels("panel #4", "a copy of panel #3!");
    std::this_thread::sleep_for(short_delay);
    panel4.move({10, 5}, false); // NOLINT
    std::this_thread::sleep_for(short_delay);

    // NOLINTNEXTLINE
    for(int i = 0; i < 10; i++) {
      // NOLINTNEXTLINE
      panel4.move({(10 + i), (5 + i)}, false);
      std::this_thread::sleep_for(short_delay / 2);
    }
  }


  bool Application::on_key(int key_code) {
    std::clog << "on_key(): " << key_code<< "\n";
    if(key_code == KEY_Q || key_code == KEY_ESC) {
      std::clog << "q\n";
      quit();
    }
    return true;
  }
} // namespace y44::ctimer

