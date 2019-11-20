#pragma once
#include <cstddef>

namespace y44::curses_lib{
  struct Size {
    public:
      int width = 0;
      int height = 0;

    public:
      constexpr Size() = default;
      constexpr Size (int w, int h) : width(w), height(h) { }

     Size operator+(const Size& other) { return Size(*this) += other; }
      Size& operator+=(const Size& other) {
       width += other.width;
        height += other.height;

       return *this;
      }
    
     Size operator-(const Size& other) { return Size(*this) -= other; }
      Size& operator-=(const Size& other) {
       width -= other.width;
        height -= other.height;

        return *this;
      }
  };
}; // namespace y44::curses_lib

