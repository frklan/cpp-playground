
#include "app.h"
#include "MainWindow.h"

#include <iostream>
#include <memory>

App::App() {
  std::clog << "\n\n";
  std::clog << "--- testing native c++ wrapper for curses ---\n";
  std::clog << version();
}

int App::run() {
  auto mainWindow = std::make_shared<MainWindow>();
  return mainWindow->run();
}
