#include "Application.h"
#include "curses_lib/Application.h"
#include "curses_lib/Panel.h"
#include <iostream>
#include <memory>

// NOLINTNEXTLINE 
int main() {
  std::clog << "Now running curses_lib/Application\n";
  y44::ctimer::Application app{};
  app();
  
  std::clog << "app done\n";
  return 0;
}
