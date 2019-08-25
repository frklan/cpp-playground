
#include "Logger.h"
#include "LogView.h"

#include <algorithm> 
#include <boost/signals2.hpp>
#include <ncursesw/cursesp.h>
#include <utility>
#include <vector>

namespace y44 {
  LogView::LogView(const int nlines, const int ncols, const int begin_y, const int begin_x) 
    : y44::ScrollablePanel(nlines, ncols, begin_y, begin_x) {
    this->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    this->refresh();

    this->onLogConnection = y44::Logger::getInstance().connect(y44::Logger::stype_t(&y44::LogView::onLog, this, _1));
  }

  int LogView::onKey(const int key) {
    if(key == '\n') {
      appendText(currentInput);
      currentInput.clear();
      clearRow(this->maxy() - 1);
    } else if(key == KEY_UP) {
      this->scroll(-1);
    } else if( key == KEY_DOWN) {
      this->scroll(1);
    } else if(key < KEY_MIN) {
      currentInput += static_cast<char>(key);
      auto displayString = currentInput.substr(0, static_cast<size_t>(this->maxx()) - 1);
      this->printw(this->maxy() - 1, 1, "%s", displayString.c_str());
    }
    LogView::redraw();
    return 0;
  }

  void LogView::onLog(const std::string& message) {
    if(isViewActive()) {
      //std::clog << "LogView::onLog (" + std::get<0>(this->getLabel()) << "): " << message << '\n';
      this->appendText("[Logged] " + message);
    }
  }
} // namespace y44 
