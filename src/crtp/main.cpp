#include "version.h"
#include <iostream>

/********** Reusing implementation ************/

template<class T>
class numerical_functions {
  public:
    void scale(double factor) {
      T& u = static_cast<T&>(*this);
      u.setValue(u.getValue() * factor);
    }
  private:
    numerical_functions() = default;
    friend T;
};

class filter: public numerical_functions<filter> {
  public:
    void setValue(double v) { m_value = v; }
    [[nodiscard]] double getValue() const { return m_value; }

  private:
    double m_value = 0;
};

class sensitivity : public numerical_functions<sensitivity> {
  public:
    void setValue(double v) { m_value = v * 2; }
    [[nodiscard]] double getValue() const { return m_value; }

  private:
    double m_value;

};


static void crtp_reuse_impl();
static void crtp_reuse_impl() {

  std::clog << "-- crtp_reuse_impl() --\n";
  
  filter f;
  f.setValue(13.37);
  std::clog << "filter value = " << f.getValue() << '\n';

  std::clog << "scaling\n";
  f.scale(0.2);
  std::clog << "filter value = " << f.getValue() << '\n';
  
  sensitivity s{};
  s.setValue(42);
  std::clog << "s value = " << s.getValue() << '\n';

  std::clog << "scaling\n";
  s.scale(13.37);
  std::clog << "s value = " << s.getValue() << '\n';
}

/********** Reusing implementation ************/


/********** static interface *********/

template<typename T>
struct crtp {
  [[nodiscard]] T& underlaying() { return static_cast<T&>(*this); }
  [[nodiscard]] const T& underlaying() const { return static_cast<const T&>(*this); }
};

template<typename T>
struct numerical_functions_crtp : crtp<T> {
  public:
    void scale(double factor) { this->underlaying().setValue(this->underlaying().getValue() * factor); }

  private:
    numerical_functions_crtp() = default;
    friend T;
};

class sensitivity_crtp : public numerical_functions_crtp<sensitivity_crtp> {
  public:
    void setValue(double v) { m_value = v * 2; }
    [[nodiscard]] double getValue() const { return m_value; }

  private:
    double m_value;
};

static void crtp_static_impl();
static void crtp_static_impl() {
  std::clog << "-- crtp_static_impl() --\n";

  sensitivity_crtp s{};
  s.setValue(42);
  std::clog << "s value = " << s.getValue() << '\n';

  std::clog << "scaling\n";
  s.scale(13.37);
  std::clog << "s value = " << s.getValue() << '\n';
}

/********** static interface *********/


int main(int /*argc*/, char** /*argv*/)
{
  std::clog << "<-- CRTP -->\n";
  std::clog << version() << '\n';

  crtp_reuse_impl();
  crtp_static_impl();

  return 0;
}
