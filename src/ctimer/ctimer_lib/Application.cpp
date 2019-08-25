#include "Application.h"
#include "MainWindow.h"

#include <iostream>
#include <memory>
#include <version.h>

namespace y44 {
  Application::Application() { 
    std::clog << "\n\nApplication::Application()\n";
    std::clog << "--- C++ Curses based  timer app ---\n";
    std::clog << "Version " << version() << '\n';

    mainWindow = std::make_unique<y44::MainWindow>();

  }

  int Application::run() {
    return mainWindow->run();
  }

} // namespace y44

