
#include "Logger.h"
#include "LogView.h"

#include <ncursesw/cursesp.h>
#include <utility>
#include <vector>

LogView::LogView(const int nlines, const int ncols, const int begin_y, const int begin_x) 
  : Panel(nlines, ncols, begin_y, begin_x)
{
  this->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  this->refresh();

}

int LogView::onKey(const int key) {
  if(key == '\n') {
    history.push_back(currentInput);
    currentInput.clear();
  } else {
    currentInput += static_cast<char>(key);
    this->printw(this->maxy() - 1, 2, "%s", currentInput.c_str());
  }

  auto numberVisibleRows = history.size();
  auto dialogHeight = static_cast<size_t>(this->maxy()) - 3 ;

  if(numberVisibleRows > dialogHeight) {
    numberVisibleRows = dialogHeight;
  }

  int row = 1;
  for(auto i = history.size() - numberVisibleRows; i < history.size(); i++) {
    this->printw(row + 1, 2, "%s", history[i].c_str());
    row++;
    std::clog << i << ", "; 
  }

  LogView::redraw();
  return 0;
}

void LogView::onLog(const std::string& message) {
  std::clog << "LogView::onLog (" + std::get<0>(this->getLabel()) << "): " << message << '\n';
}

