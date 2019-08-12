#pragma once

#include "MainWindow.h"

#include <ncursesw/cursesp.h>
#include <memory>

class Application {
  public:
    Application();
    int run();

  private:
    std::unique_ptr<MainWindow> mainWindow;
};

