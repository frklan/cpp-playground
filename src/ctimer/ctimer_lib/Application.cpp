#include "Application.h"
#include "MainWindow.h"

#include <iostream>
#include <memory>
#include <version.h>


Application::Application() { 
  std::clog << "\n\nApplication::Application()\n";
  std::clog << "--- C++ Curses based  timer app ---\n";
  std::clog << "Version " << version() << '\n';

  mainWindow = std::make_unique<MainWindow>();

}

int Application::run() {
  return mainWindow->run();
}
