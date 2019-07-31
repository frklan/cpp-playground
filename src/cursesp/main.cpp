#include "cursesp_lib/app.h"
#include <iostream>

int main() {
  try {
    App app;
    return app();
  } catch(std::exception& e) {
    std::cerr << e.what();
    return -1;
  }
}

// we could also remove main() and do like so:
//static App app;
