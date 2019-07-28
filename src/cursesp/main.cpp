#include "cursesp_lib/app.h"
#include <memory>

int main() {
  try {
    auto app = std::make_shared<App>();
    return app->run();
  } catch(std::exception& e) {
    std::cerr << e.what();
    return -1;
  }

}

