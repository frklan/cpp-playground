#pragma once

#include <ncurses.h>
#include <string>
#include <vector>

struct WindowSize {
  size_t height;
  size_t width;
};


class Ncs {
  public:
    int run();

  private:
    WINDOW* screen_win = nullptr;
    WINDOW* history_win = nullptr;
    WINDOW* command_win = nullptr;
    std::vector<std::string> history;
    
    WindowSize history_size;

    void addHistory(const std::string& entry);
    void createWindows();
    void destroyWindows();
};

