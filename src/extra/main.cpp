#include "extra.h"
#include <iostream>

int main() {
  std::clog << "--- extra ---\n";
  std::clog << R"(a "full" project)" << '\n';
  extra();
  
  return 0;
}
