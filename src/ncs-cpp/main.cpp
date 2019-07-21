#include "ncscpp_lib/ncscpp.h"
#include <iostream>
#include <version.h>


int main() {
  std::clog << "--- ncurces c++ test ---\n";
  std::clog << "Build version: " << version() << '\n';
  
  Ncscpp ncs;
  ncs.run();
  
  return 0;
}
