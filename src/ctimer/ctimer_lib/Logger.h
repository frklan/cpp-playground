#pragma once

#include <boost/signals2.hpp>
#include <iostream>
#include <memory>
#include <string>

namespace y44 {
  class Logger {
    public:
      static Logger& getInstance(){
        static Logger logger;
        return logger; 
      }

      static void info(std::string msg) {
        //std::clog << msg << '\n';
        Logger::getInstance().onLogSignal(msg);
      }
      
      ~Logger() = default;
      
      typedef boost::signals2::signal<void (std::string message)> signal_t;
      typedef signal_t::slot_type stype_t;
      boost::signals2::connection connect(const stype_t &subscriber) {
        return onLogSignal.connect(subscriber);
      }

    private:
      signal_t onLogSignal;
      
      Logger() = default;
      Logger(const Logger&) = delete;
      Logger& operator=(const Logger&) = delete;
      Logger(Logger&&) = delete;
      Logger & operator=(Logger&&) = delete;
  };
} // namespace y44
