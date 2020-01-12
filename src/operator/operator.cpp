#include <iostream>


class Widget {

  public:
    Widget() = default;
    explicit Widget(int d) { 
      std::clog << "Widget(int)\n";
      this->data = d; 
    }

    explicit Widget(double d) {
      std::cout << "Widget(double)\n";
      this->data = d;
    }

    Widget operator+(const Widget& other) {
      std::clog << "Widget operator+(const Widget& other)\n";

      return Widget(data + other.data);
    }

    Widget operator+(const int& other) {
      std::clog << "Widget operator+(const int& other)\n";

      return Widget(data + other);
    }

//    Widget operator+(const int&& other) {
//      std::clog << "Widget operator+(const int&& other)\n";
//
//      return Widget(data + other);
//    }

    Widget& operator+=(const Widget& other) {
      std::clog << "Widget& operator+=(const Widget& other)\n";
      this->data += other.data;
      return *this;
    }

    Widget& operator+=(const int other) {
      std::clog << "widget& operator+=(const int other)\n";
      this->data += other;
      return *this;
    }

    friend Widget operator+(const Widget& lhs, const Widget& rhs);
    friend Widget operator+(int lhs, const Widget& rhs);

    private:
      int data = 42;

};

Widget operator+(const Widget& lhs, const Widget& rhs) {
  std::clog << "Widget operator+(const Widget&, const Widget&)\n";

  return Widget(lhs.data + rhs.data);
}

Widget operator+(int lhs, const Widget& rhs) {
  std::clog << "Widget operator+(int, Widget&)\n";
  return Widget(lhs + rhs.data);
}


int main(int /*argc*/, char** /*argc*/) {

  Widget w1;
  Widget w2;
  std::clog << "1: ";
  Widget w3 = w1 + w2;
  
  std::clog << "2: ";
  w3 = w3 + 1337;
  
  std::clog << "3: ";
  w3 = 1337 + w3;

  std::clog << "4: ";
  w3 += w2;

  std::clog << "5: ";
  w3+= 23;

  return 0;
}

