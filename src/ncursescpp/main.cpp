#include "ncursescpp_lib/ncursescpp.h"
#include <iostream>
#include <version.h>


int main() {
  std::clog << "--- ncursescpp test ---\n";
  std::clog << "Build version: " << version() << '\n';
  
  Ncursescpp ncursescpp;
  ncursescpp.run();
  
  return 0;
}
