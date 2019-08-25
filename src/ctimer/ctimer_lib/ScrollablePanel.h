#pragma once

#include "Panel.h"

#include <string>
#include <vector>

namespace y44 {
  class ScrollablePanel : public y44::Panel {
    public:
      ScrollablePanel() = delete;
      ScrollablePanel(int nlines, int ncols, int begin_y, int begin_x); 
      virtual ~ScrollablePanel() override = default;

      virtual void appendText(const std::string& text);
      virtual void insertText(const std::string& text, const size_t lineNumber);
      virtual void clearText();

      virtual void setAutoscroll(const bool mode);
      virtual void setScrollPosition(const size_t pos);
      virtual void scroll(const int16_t rows);
    private:
      std::vector<std::string> history;
      bool autoScroll = false;
      size_t scrollPosition = 0;

      void printHistory();
  };
} // namespace y44

