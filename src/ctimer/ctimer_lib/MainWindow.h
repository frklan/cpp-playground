#pragma once

#include "LogView.h"
#include "ScrollablePanel.h"

#include <iostream>
#include <ncursesw/cursesp.h>
#include <memory>
#include <vector>

namespace y44 {   
  constexpr int16_t KEY_TAB = 9;
  constexpr int16_t KEY_ESC = 27;

  class MainWindow : public NCursesPanel {
    public:
      MainWindow();

      virtual int run();

    private:
      std::shared_ptr<y44::ScrollablePanel> getActiveView();
      std::shared_ptr<y44::ScrollablePanel> getView(const std::string& /*viewName*/);
      void activateNextView();
      void addView(const std::shared_ptr<y44::ScrollablePanel>& view);

      std::unique_ptr<y44::Panel> inputPanel = nullptr;
      std::unique_ptr<NCursesPanel> titlebar = nullptr;
      std::vector<std::shared_ptr<y44::ScrollablePanel>> views;
      size_t activeViewIndex = 0;
      std::string currentInput = "";
  };
} // namespace y44
