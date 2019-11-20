#pragma once
#include <cstddef>

namespace y44::curses_lib{
  struct Position{
    public:  
      int x = 0;
      int y = 0;

    public:
      constexpr Position() = default;
      constexpr Position (int x_pos, int y_pos) : x(x_pos), y(y_pos) { }

      Position operator+(const Position& other) { 
        return Position(*this) += other; 
      }
      
      Position& operator+=(const Position& other) {
        x += other.x;
        y += other.y;

       return *this;
      }
    
     Position operator-(const Position& other) { return Position(*this) -= other; }
      Position& operator-=(const Position& other) {
        x -= other.x;
        y -= other.y;

        return *this;
      }
  };
}; // namespace y44::curses_lib

