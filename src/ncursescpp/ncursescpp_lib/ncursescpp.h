#pragma once

#include <ncursescpp/ncursescpp.hpp>
#include <vector>

class Ncursescpp {
  public:
    int run();

  private:
    size_t historyWindow;
    std::vector<std::string> history;
    int height; 
    int width;

    void addHistory(const std::string&);
};

