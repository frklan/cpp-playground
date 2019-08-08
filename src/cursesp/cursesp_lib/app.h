#pragma once

#include <iostream>
#include <ncursesw/cursesapp.h>
#include <ncursesw/cursesw.h>
#include <ncursesw/cursesp.h>
#include <memory>

struct Size {
  int height;
  int width;
};
  
class App : public NCursesApplication {

  public:
    App();
    virtual ~App() override ;
    int run() override;


  private:
    std::unique_ptr<NCursesPanel> titlebarWin = nullptr;
    std::unique_ptr<NCursesPanel> logWin = nullptr;
    std::unique_ptr<NCursesPanel> timerWin = nullptr;

    uint16_t count = 0;

    int loop();
};

