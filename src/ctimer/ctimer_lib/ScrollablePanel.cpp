#include "ScrollablePanel.h"
#include "Panel.h"

#include <algorithm>
#include <exception>
#include <iostream>

ScrollablePanel::ScrollablePanel(int nlines, int ncols, int begin_y, int begin_x) :
  Panel(nlines, ncols, begin_y, begin_x) {
}


void ScrollablePanel::appendText(const std::string& text) {
  auto s = text;
  std::replace(s.begin(), s.end(), '\n', ' '); 
  this->history.push_back(s);
  
  if(this->autoScroll) {
    auto height = static_cast<size_t>(this->maxy() - 2);
    auto lineCount = history.size();
    
    if(lineCount < height) {
      this->scrollPosition = 0;
    } else {
      this->scrollPosition = lineCount - height;
    }
  }
  
  this->printHistory();
}

void ScrollablePanel::insertText(const std::string& text, const size_t lineNumber) {
  auto height = static_cast<size_t>(this->maxy() - 2);
  auto lineCount = history.size();
  
  if(lineNumber < lineCount) {
    auto dest = this->history.begin() + lineNumber + 1;
    this->history.insert(dest, text);
      
    if(lineCount > height) {
     this->scrollPosition++;
    }
    this->printHistory();
  } else {
    appendText(text);
  }
}

void ScrollablePanel::clearText() {
  this->history.clear();
  this->setScrollPosition(0);
  this->printHistory();
}

void ScrollablePanel::setScrollPosition(const size_t pos) {
  this->scrollPosition = std::clamp(pos, static_cast<size_t>(0), this->history.size() - 1);
}

void ScrollablePanel::printHistory() {
  auto numberVisibleRows = history.size();


  int row = 1;
  for(auto i = scrollPosition; i < numberVisibleRows; i++) {
    clearRow(row);
    this->printw(row, 1, "%s", (history[i].substr(0, static_cast<size_t>(this->maxx() - 2))).c_str());
		row++;
  }

  ScrollablePanel::redraw();
}

