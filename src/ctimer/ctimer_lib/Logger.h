#pragma once

#include <iostream>
#include <memory>
#include <string>

class Logger {
  public:
    static Logger& getInstance(){
      static Logger logger;
      return logger; 
    }

    static void info(std::string msg) {
      std::clog << msg << '\n';
    }

  private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger & operator=(Logger&&) = delete;
};

