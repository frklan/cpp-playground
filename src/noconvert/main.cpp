#include <iostream>

// ----------------------------- Working ------------------------------ //
class Working {
  public:
    Working() = delete;
    explicit Working(int val) { _x = val; }

    template<typename T> T x();
  
  private:
    int _x;
};

template<> int Working::x<int>() {
  std::clog << "Working::x() int version\n";
  return static_cast<int>(_x);
}

template<> uint16_t Working::x<uint16_t>() {
  std::clog << "Working:x() uint16_t version\n";
  
  uint16_t val;

  if(_x < 0) {
    val = 0;
  } else if(_x > std::numeric_limits<uint16_t>::max()) {
    val = std::numeric_limits<uint16_t>::max();
  } else {
    val = static_cast<uint16_t>(_x);
  }

  return val;
}
// ----------------------------- Working ------------------------------ //



// ----------------------------- Best ------------------------------ //
class Best {
  public:
    Best() = delete;
    explicit Best(int val) { _x = val; }

    template<typename T> T x();

  private:
    int _x;
};

template<typename T>
struct dependent_false: std::false_type {};

template<typename T> T Best::x() {
  static_assert( dependent_false<T>::value, "Type specialization not allowed");
};

template<> int Best::x<int>() {
  std::clog << "Best::x() int version\n";
  return static_cast<int>(_x);
}

template<> uint16_t Best::x<uint16_t>() {
  std::clog << "Best:x() uint16_t version\n";
  
  uint16_t val;

  if(_x < 0) {
    val = 0;
  } else if(_x > std::numeric_limits<uint16_t>::max()) {
    val = std::numeric_limits<uint16_t>::max();
  } else {
    val = static_cast<uint16_t>(_x);
  }

  return val;
}
// ----------------------------- Best ------------------------------ //

// NOLINTNEXTLINE 
int main() {
  std::clog << "-- Working -> cryptic compile time error --\n";
  Working w{-1337};
  std::clog << "requesting Working.x<uint16_t>().. " << w.x<uint16_t>() << '\n';
  std::clog << "requesting Working.x<int>().. " << w.x<int>() << '\n';
  // Will not compile
  // std::clog << "requesting Working.x<float>().. " << w.x<float>() << '\n';
  std::clog << "-- Working --\n";

  std::clog << "-- Best -> more readable compile time error --\n";
  Best b(42);
  std::clog << "requesting Best<uint16_t>().. " << b.x<uint16_t>() << '\n';
  std::clog << "requesting Best<int>().. " << b.x<int>() << '\n';
  // Will not compile:
  //std::clog << "requesting Best<float>().. " << b.x<float>() << '\n';
  std::clog << "-- Best solution --\n";

  return 0;
}
