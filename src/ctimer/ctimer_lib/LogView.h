#pragma once

#include "Panel.h"
#include <boost/signals2.hpp>
#include <ncursesw/cursesp.h>
#include <string>
#include <vector>

class LogView : public Panel {
  public:
    LogView(const int nlines, const int ncols, const int begin_y, const int begin_x);

    int onKey(const int key);
    void onLog(const std::string&);
    
  private:
    std::string currentInput = "";
    std::vector<std::string> history;
};


