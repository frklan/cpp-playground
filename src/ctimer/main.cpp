#include "ctimer_lib/Application.h"
#include <iostream>

int main() {
  try {
    Application app;
    return app.run();
  } catch(std::exception& e) {
    std::cerr << e.what();
    return -1;
  }
}
