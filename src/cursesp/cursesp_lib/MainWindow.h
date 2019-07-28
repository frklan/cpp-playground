#pragma once

#include <libredeo/intervall.h>
#include <memory>
#include <ncursesw/cursesw.h>
#include <ncursesw/cursesp.h>


class MainWindow : public NCursesPanel {
  public:
    MainWindow();
    virtual ~MainWindow();
    
    int run();
  private:
    std::unique_ptr<NCursesPanel> titlebarWin = nullptr;
    std::unique_ptr<NCursesPanel> logWin = nullptr;
    std::unique_ptr<NCursesPanel> timerWin = nullptr;
    uint8_t count = 0;
};

