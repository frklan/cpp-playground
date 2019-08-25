#pragma once

#include "LogView.h"

#include <iostream>
#include <ncursesw/cursesp.h>
#include <memory>
#include <vector>

namespace y44{   
  constexpr int16_t KEY_TAB = 9;
  constexpr int16_t KEY_ESC = 27;

  class MainWindow : public NCursesPanel {
    public:
      MainWindow();

      virtual int run();

    private:
      std::shared_ptr<Panel> getActiveView();
      std::shared_ptr<Panel> getView(const std::string& /*viewName*/);
      void activateNextView();
      void addView(const std::shared_ptr<Panel>& view);

      std::unique_ptr<NCursesPanel> titlebar = nullptr;
      std::vector<std::shared_ptr<Panel>> views;
      size_t activeViewIndex = 0;
  };
} // namespace y44
