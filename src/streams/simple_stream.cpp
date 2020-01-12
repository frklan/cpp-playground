
#include <iostream>
#include <sstream>
#include <thread>

constexpr std::string_view RED = "\u001b[31m";
constexpr std::string_view YELLOW = "\u001b[33m";
constexpr std::string_view RESET = "\u001b[0m";

class Test {
  public:
    Test() = default;
    Test(const Test&) = default;
    Test(Test&&) = default;
    Test& operator=(const Test&) = default;
    Test& operator=(Test&&) = default;

    ~Test() { this->flush(); }

    friend std::istream& operator>>(std::istream& is, Test& c);

    [[nodiscard]] std::string getData() const { return data; }

    void flush() {
      if(!data.empty()) {
        std::clog << '\n' << YELLOW << "[Test::flush()]: " << RESET << data << '\n';
        data.clear();
      }
    }

    Test& operator<<(const std::string& s) {
      data += s;

      while(data.find('\n') != std::string::npos) {
        auto pos = data.find('\n');
        auto subString = data.substr(0, pos);
        data.replace(0, pos + 1, "");
        
        std::clog << YELLOW << subString << RESET << '\n';
      }
      return *this;
    }
    
    Test& operator<<(const char c) {
      operator<<(std::string(1, c));
      return *this;
    }

    Test& operator<<(int s) {
      data += std::to_string(s);
      return *this;
    }

  private:
    std::string data;
};

static std::ostream& operator<<(std::ostream& os, const Test& t) {
  if(!t.getData().empty()) {
    os << RED << "[global operator<<]: " << RESET << "current data is: " << t.getData();
  }
  return os;
}


int main(int /* unused*/, char** /*unused*/) {
  Test t;
  
  std::clog << "-- streaming data to t --\n";
  t << std::string("hello world!");

  t << ". more data\ncomes here!.";

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2s);
  t << '\n';

  
  std::this_thread::sleep_for(1s);
  t << "Data still in the buffer will be flushed upon destruction..";
  return 0;
}

