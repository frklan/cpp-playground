#include "cppcurses_lib/cppcurses.h"
#include <iostream>
#include <version.h>


int main() {
  std::clog << "--- CPPurses c++ test ---\n";
  std::clog << "Build version: " << version() << '\n';
  
  Cppcurses ncs;
  ncs.run();
  
  return 0;
}
