#pragma once

#include "Panel.h"

#include <string>
#include <vector>

class ScrollablePanel : public Panel {
  public:
    ScrollablePanel() = delete;
    ScrollablePanel(int nlines, int ncols, int begin_y, int begin_x); 
    virtual ~ScrollablePanel() override = default;

		virtual void appendText(const std::string& text);
    virtual void insertText(const std::string& text, const size_t lineNumber);
    virtual void clearText();

    virtual void setScrollPosition(const size_t pos);
  private:
    std::vector<std::string> history;
    bool autoScroll = true;
    size_t scrollPosition = 0;

		void printHistory();
};

