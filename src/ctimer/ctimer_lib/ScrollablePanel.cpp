#include "ScrollablePanel.h"
#include "Panel.h"

#include <algorithm>
#include <exception>
#include <iostream>

namespace y44 {
  ScrollablePanel::ScrollablePanel(int nlines, int ncols, int begin_y, int begin_x) :
    y44::Panel(nlines, ncols, begin_y, begin_x) {
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

  void ScrollablePanel::setAutoscroll(const bool mode) {
    this->autoScroll = mode;
  }

  void ScrollablePanel::setScrollPosition(const size_t pos) {
    this->scrollPosition = std::clamp(pos, static_cast<size_t>(0), this->history.size() - 1);
  }

  void ScrollablePanel::scroll(const int16_t rows) {
    int64_t historyCount = this->history.size();

    std::clog << "current scrollPos = " << this->scrollPosition;
    int32_t newPos = rows + this->scrollPosition;
    std::clog << ", new scrollPos = " << newPos;


    if(newPos >= historyCount) {
      setScrollPosition(historyCount - 1);
      std::clog << ", (beyond last line)";
    } else if(newPos < 0) {
      setScrollPosition(0);
      std::clog << " (before first line)";
    } else {
      setScrollPosition(static_cast<size_t>(newPos));
    }
    std::clog << ", adjusted scrollPos = " << this->scrollPosition << '\n';


    this->printHistory();
    ScrollablePanel::redraw();
  }

  void ScrollablePanel::printHistory() {
    auto numberVisibleRows = history.size();

    int row = 1;
    for(auto i = scrollPosition; i < numberVisibleRows; i++) {
      clearRow(row);
      this->printw(row, 1, "%s", (history[i].substr(0, static_cast<size_t>(this->maxx() - 2))).c_str());
      row++;
      if(row > this->maxy() -2) {
        break;
      }
    }

    // clear remaining rows of dialog (if any)
    for(auto i = row; i < this->maxy() - 1; i++) {
      clearRow(i);
    }

    ScrollablePanel::redraw();
  }
} // namespace y44

