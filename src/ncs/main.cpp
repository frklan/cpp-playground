#include "ncs_lib/ncs.h"
#include <version.h>

#include <iostream>

int main() {
  std::clog << "--- ncurces test ---\n";
  std::clog << "Build version: " << version() << '\n';
  
  Ncs ncs;
  ncs.run();
  
  return 0;
}
