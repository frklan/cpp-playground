#pragma once
#include <cstddef>
#include <cstdint>

namespace y44::noconvert {
  struct Size {
    public:
      uint16_t width = 0;
      uint16_t height = 0;

    public:
      constexpr Size() = default;
      constexpr explicit Size (uint16_t w, uint16_t h) : width(w), height(h) { }

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
}; // namespace y44::noconvert {

