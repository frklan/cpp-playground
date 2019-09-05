#include "Logger.h"
#include "LogView.h"
#include "MainWindow.h"

#include <iostream>
#include <memory>
#include <ncursesw/cursesp.h>
#include <vector>

namespace y44 {
  constexpr uint16_t TITLEBAR_HEIGHT = 3;

  MainWindow::MainWindow() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(true);
    start_color();
    clear();

    y44::Logger::info("MainWindow instantiating");
    
    titlebar = std::make_unique<NCursesPanel>(TITLEBAR_HEIGHT, this->cols(), 0, 0);
    titlebar->attron(COLOR_PAIR(1));
    titlebar->printw(1, titlebar->cols() / 2, "ctimer!");
    titlebar->attroff(COLOR_PAIR(1));
    titlebar->refresh();

    inputPanel = std::make_unique<Panel>(1, this->cols(), this->lines() - 1, 0);
    
    auto logView = std::make_shared<y44::LogView>(this->lines() - 4, this->cols() / 2, 3, 0);
    logView->label("logView");
    logView->setAutoscroll(true);
    this->addView(logView);
    this->activateNextView();

    auto logView2 = std::make_shared<y44::LogView>((this->lines() - 4) / 2, this->cols() / 2, 3, this->cols() / 2);
    logView2->label("logView2");
    this->addView(logView2);

    auto logView3 = std::make_shared<y44::LogView>((this->lines() - 4) / 2, this->cols() / 2, this->lines() / 2 + 1 , this->cols() / 2);
    logView3->label("Log Viewer # 3");
    this->addView(logView3);
    
    this->refresh();
    y44::Logger::info("App started!");
  }

  int MainWindow::run() {
    y44::Logger::info("MainWindow loop begin");
    
    int chr; 
    auto quit = false;
    do {
      chr = getch();
      if(chr == -1) {
        continue;
      }

      if(chr == KEY_RESIZE) {
          y44::Logger::info("KEY_RESIZE event detected");
      } else if(chr == KEY_TAB) { 
          y44::Logger::info("Switching active view");
          this->activateNextView();
      } else if(chr == KEY_F(1)) {
          y44::Logger::info("F1 key pressed");
      } else if(chr == 'q' || chr == KEY_ESC) {
          y44::Logger::info("KEY_ESC/q pressed, exiting!");
          quit = true;
      } else if(chr == KEY_UP) {
          this->getActiveView()->scroll(-1);
      } else if(chr == KEY_DOWN) {
          this->getActiveView()->scroll(1);
      } else if(chr == '\n') {
        this->getActiveView()->appendText(this->currentInput);
        this->inputPanel->clear();
        this->currentInput.clear();
        this->inputPanel->refresh();
      } else if(chr < KEY_MIN) {
        this->currentInput += static_cast<char>(chr);
        this->inputPanel->clear();
        this->inputPanel->printw(0, 1, "%s", currentInput.c_str());
        this->inputPanel->refresh();
      }
      
    } while(!quit);

    endwin();
    return 0;
  }

  std::shared_ptr<y44::ScrollablePanel> MainWindow::getActiveView() {
    return views[activeViewIndex];
  }

  std::shared_ptr<y44::ScrollablePanel> MainWindow::getView(const std::string& /*viewName*/) {
    return nullptr;
  }

  void MainWindow::activateNextView() {
    views[activeViewIndex]->onDeactivate();
    activeViewIndex++;
    if(activeViewIndex > views.size() - 1) {
      activeViewIndex = 0;
    }
    views[activeViewIndex]->onActivate();
  }

  void MainWindow::addView(const std::shared_ptr<y44::ScrollablePanel>& view) {
    views.push_back(view);
  }
} // namespace y44
