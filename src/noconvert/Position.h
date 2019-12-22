#pragma once
#include <cstddef>
#include <iostream>

namespace y44::noconvert{
/*
  template<typename T>
  struct dependent_false: std::false_type {};
  template<typename T> T Best::x() {
    static_assert( dependent_false<T>::value, "Type specialization not allowed");
  };

  template<> int Best::x<int>() {
    std::clog << "Best::x() int version\n";
    return static_cast<int>(_x);
  }
*/

  template<class T> class any_types { };
  
  template<class T>
  struct integral_types {
    static_assert(std::is_integral<T>::value, "Type specialization not supported");
  };

  template <class T>
  struct specific_types {
    static_assert(std::is_same<T, int>::value || std::is_same<T, uint16_t>::value, "Type specialization not supported");
  };


  template<class T, class Enabled_Types = integral_types<T>>
  struct Property {
    public:
      Property& operator=(const T& value) {
        m_value = value;
        return *this;
      }

      operator int() const; 
      operator uint16_t() const;

      friend std::ostream& operator<<(std::ostream& os, const Property& p) {
        os << p.m_value;
        return os;
      }

      void foo();

      Property& operator+=(const T& other) {
        m_value = m_value + other;
        return *this;
      }

      Property& operator-=(const T& other) {
        m_value = m_value - other;
        return *this;
      }

    private:
      T m_value;
  };

    template<>
    void Property<int>::foo() {
      std::cout << "foo@int!!\n"; 
    }
  
    template<>
    void Property<uint16_t>::foo() {
      std::cout << "foo@uint16_t!!\n"; 
    }

    template<class T, class E>
    void Property<T, E>::foo() {
      std::clog << "foo\n";
    }

    template<class T, class E>
    Property<T, E>::operator uint16_t() const { 
      return static_cast<uint16_t>(m_value); 
    }
    
    template<class T, class E>
    Property<T, E>::operator int() const { 
      return static_cast<int>(m_value); 
    }

  struct Position{
    public:
      int x = 0;
      int y = 0;

      Property<int> p;

    public:
      Position() = default;
      Position (int x_pos, int y_pos) : x(x_pos), y(y_pos) { }

      Position(float x_pos, float y_pos) {
        std::clog << "--> Float constructor <--\n";
        x = static_cast<int>(x_pos);
        y = static_cast<int>(y_pos);
      }

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
}; // namespace y44::noconvert_lib

