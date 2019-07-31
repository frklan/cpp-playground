#pragma once

#include <ncursesw/cursesapp.h>
#include <ncursesw/cursesw.h>
#include <ncursesw/cursesp.h>
#include <memory>

class App : public NCursesApplication {

  public:
    App();
    ~App();
    int run();
  
  private:
    std::unique_ptr<NCursesPanel> titlebarWin = nullptr;
    std::unique_ptr<NCursesPanel> logWin = nullptr;
    std::unique_ptr<NCursesPanel> timerWin = nullptr;
    uint8_t count = 0;

    int loop();
};

