#include "ctimer_lib/Application.h"
#include <iostream>
#include <thread>

#include "curses_lib/Panel.h"

int main() {
 /* try {
    y44::Application app;
    return app.run();
  } catch(std::exception& e) {
    std::cerr << e.what();
    return -1;
  }
*/
  std::clog << "Now running curses_lib/Panel\n";
  using namespace std::chrono_literals;

  constexpr auto short_delay{1.5s};
  constexpr auto long_delay{10s};

  constexpr y44::curses_lib::position p1p{25, 45};
  constexpr y44::curses_lib::size p1s{10,5};
  auto panel = y44::curses_lib::Panel(p1s, p1p);
  panel.set_labels("A long label that will not fit in the titlebar!", "A shorter bottom label");
  

  std::this_thread::sleep_for(short_delay);

  constexpr y44::curses_lib::position p2p{25, 45};
  constexpr y44::curses_lib::size p2s{15, 10};
  auto panel2 = y44::curses_lib::Panel(p2s, p2p);
  panel2.set_labels("Panel #2", "");
  std::this_thread::sleep_for(short_delay);
  panel2.get_label();
  

  constexpr y44::curses_lib::position p3p{25, 45};
  constexpr y44::curses_lib::size p3s{20, 15};
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
  panel4.move({10, 5}, false);
  std::this_thread::sleep_for(short_delay);

  for(size_t i = 0; i < 10; i++) {
    panel4.move({(10 + i), (5 + i)}, false);
    std::this_thread::sleep_for(short_delay / 2);
  }

  std::this_thread::sleep_for(long_delay);

  return 0;
}
