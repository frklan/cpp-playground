#include <iostream>

#include "Template.h"

// NOLINTNEXTLINE 
int main() {
  std::clog << " ------------\n";
  std::clog << " Template App \n";
  std::clog << " ------------\n";

  y44::Application app{};
  
  return app.run();
}
