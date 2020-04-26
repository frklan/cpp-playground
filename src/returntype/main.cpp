#include <iostream>

#include <memory>
#include <string>

class from_string
{
    const std::string m_str;
  public:
    from_string(const char *str) : m_str(str) {}
    
    template <typename type>
    operator type() {
      if constexpr(std::is_same_v<type, float>) {
        return stof(m_str);
      } else if(std::is_same_v<type, int>) {
        return stoi(m_str);
      }
    }
};

int main(int /*argc*/, char** /*argv*/) {
  std::clog << "Now running Return Type Resolver\n";

  int n_int = from_string("123");
  std::cout << n_int << '\n';
  float n_float = from_string("123.111");
  std::cout << n_float << '\n';


  return 0;
}
