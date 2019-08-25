#pragma once

#include "MainWindow.h"

#include <ncursesw/cursesp.h>
#include <memory>

namespace y44 {
  class Application {
    public:
      Application();
      int run();

    private:
      std::unique_ptr<y44::MainWindow> mainWindow;
  };
} // namespace y44
