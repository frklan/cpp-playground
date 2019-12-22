#include "Position.h"
#include <iostream>
#include <type_traits>

void f1(uint16_t /*unused*/);
void f1(uint16_t /*unused*/) {};

void f2(int /*unused*/);
void f2(int /*unused*/) {};

// NOLINTNEXTLINE
int main() {
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

  return 0;
}
