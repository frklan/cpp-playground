#include "Position.h"
#include <iostream>
#include <type_traits>

template<typename T, typename Enable = void> class Coord; 

template <class T> 
class Coord<T, typename std::enable_if<std::is_same<T, int>::value || std::is_same<T, uint16_t>::value>::type> {
public:
  Coord() : m_value(0) {}

  Coord(T value) : m_value(value) { }

  operator int() const { return static_cast<int>(m_value); }// NOLINT
  operator uint8_t() const { return static_cast<uint8_t>(m_value); }// NOLINT
  operator uint16_t() const { return static_cast<uint16_t>(m_value); }// NOLINT
  operator uint32_t() const { return static_cast<uint32_t>(m_value); }// NOLINT
  operator size_t() const { return static_cast<size_t>(m_value); } // NOLINT

  friend std::ostream& operator<<(std::ostream &os, const Coord& co) {
    os << co.m_value;
    return os;
  }

  private:
    T m_value;
};



struct Test {
public:
  Coord<int> x;

  Test() = default;

  explicit Test(int val) : x(val) { }
  explicit Test(uint16_t val) : x(static_cast<int>(val)) { }
};

void f1(uint16_t /*unused*/);
void f1(uint16_t /*unused*/) {};

void f2(int /*unused*/);
void f2(int /*unused*/) {};

// NOLINTNEXTLINE
int main() {

  uint16_t u16 = 1337;

  Coord<uint16_t> c4{u16};
  std::cout << c4 << '\n';

  Coord<uint16_t> c5 = u16;
  std::cout << c5 << '\n';

  Coord<uint16_t> c6;
  c6 = u16;
  std::cout << c6 << '\n';

  Coord<int> c7;
  c7 = 42;
  std::cout << c7 << '\n';


  c7 = 2600;
  int i = c7;
  std::cout << i << '\n';

  f1(c7);
  f2(c7);


  y44::noconvert::Position pos;

  std::clog << "setting pos.p\n";
  pos.p = 15;
  int p = pos.p;
  std::clog << p << '\n';
  std::clog << "pos.p = " << pos.p << '\n';
  pos.p += 15;
  std::clog << pos.p << '\n';
  
  f1(pos.p);
  f2(pos.p);

  pos.p.foo();

  return 0;
}
