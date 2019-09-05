#pragma once

#include "Panel.h"
#include "ScrollablePanel.h"
#include <boost/signals2.hpp>
#include <ncursesw/cursesp.h>
#include <string>
#include <vector>

namespace y44 {
  class LogView : public y44::ScrollablePanel {
    public:
      LogView(const int nlines, const int ncols, const int begin_y, const int begin_x);
      virtual ~LogView() override = default;

      virtual void onLog(const std::string&);

    private:
      std::string currentInput = "";
      boost::signals2::connection  onLogConnection;
  };
} // namespace y44
