
#include "Logger.h"
#include "LogView.h"

#include <algorithm> 
#include <boost/signals2.hpp>
#include <ncursesw/cursesp.h>
#include <utility>
#include <vector>

LogView::LogView(const int nlines, const int ncols, const int begin_y, const int begin_x) 
  : Panel(nlines, ncols, begin_y, begin_x)
{
  this->border(ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  this->refresh();

  //this->onLogConnection = Logger::getInstance().connect([=](const std::string& msg){ this->onLog(msg); });
  this->onLogConnection = Logger::getInstance().connect(Logger::stype_t(&LogView::onLog, this, _1));
}

int LogView::onKey(const int key) {
  if(key == '\n') {
    add2History(currentInput);
		printHistory();
		currentInput.clear();
    clearRow(this->maxy() - 1);
  } else {
    currentInput += static_cast<char>(key);
    this->printw(this->maxy() - 1, 2, "%s", currentInput.c_str());
  }
  LogView::redraw();
  return 0;
}

void LogView::add2History(const std::string& text) {
  auto s = text;
  std::replace(s.begin(), s.end(), '\n', ' '); 
  history.push_back(s);
}

void LogView::printHistory() {
  auto numberVisibleRows = history.size();
  auto dialogHeight = static_cast<size_t>(this->maxy()) - 3 ;

  if(numberVisibleRows > dialogHeight) {
    numberVisibleRows = dialogHeight;
  }

  int row = 1;
  for(auto i = history.size() - numberVisibleRows; i < history.size(); i++) {
    clearRow(row + 1);
    this->printw(row + 1, 2, "%s", history[i].c_str());
		row++;
  }

  LogView::redraw();
}

void LogView::onLog(const std::string& message) {
  if(isViewActive()) {
		//std::clog << "LogView::onLog (" + std::get<0>(this->getLabel()) << "): " << message << '\n';
		add2History("[Logged] " + message);
		printHistory();
	}
}

  
