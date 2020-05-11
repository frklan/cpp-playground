#include "version.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>


enum COLOR {
  RED,
  GREEN, 
  BLUE
};

enum SIZE {
  SMALL,
  MEDIUM,
  LARGE
};


class Product {
  public:
    Product() = delete;
    Product(COLOR color, SIZE size, const std::string_view& name) : m_color(color), m_size(size), m_name(name) {}

    [[nodiscard]] 
    COLOR getColor() const { return m_color; }
    
    [[nodiscard]] 
    SIZE getSize() const { return m_size; }
    
    [[nodiscard]] 
    std::string getName() { return m_name; }

  private:
    COLOR m_color;
    SIZE m_size;
    std::string m_name;
};

template<typename T> struct Specification {
  virtual ~Specification() = default;
  
  [[nodiscard]] 
  virtual bool is_satisfied(const T& item) const = 0;
};

struct ColorSpecification: Specification<Product> {
  COLOR e_color;
  explicit ColorSpecification(COLOR color) : e_color(color) {}
  
  [[nodiscard]]
  virtual bool is_satisfied(const Product& item) const override { 
    return item.getColor() == e_color;
  }
};

struct SizeSpecification : Specification<Product> {
  SizeSpecification(SIZE size) : e_size(size) {}

  [[nodiscard]] 
  bool is_satisfied(const Product& item) const override { 
    return item.getSize() == e_size; 
  }

  private:
    SIZE e_size;
};


template<typename T> struct Filter {
  virtual ~Filter() = default;
  virtual std::vector<T> filter(const std::vector<T> items, const Specification<T> &spec) = 0;

};

struct BetterFilter : Filter<Product> {
  [[nodiscard]] 
  virtual std::vector<Product> filter(const std::vector<Product> items, const Specification<Product> &spec) override {
    std::vector<Product> result;

    for(auto& p: items) {
      if(spec.is_satisfied(p)) {
        result.push_back(p);
      }
    }
    return result;
  }
};



int main(int /*argc*/, char** /*argv*/)
{
  std::clog << "<-- OCP -->\n";
  std::clog << version() << "\n\n";


  std::vector<Product> p;
  p.emplace_back(Product{COLOR::RED, SIZE::SMALL, "one"});
  p.emplace_back(Product{COLOR::GREEN, SIZE::MEDIUM, "two"});
  p.emplace_back(Product{COLOR::BLUE, SIZE::SMALL, "onehundred"});

  
  BetterFilter bf;
  for(auto item : bf.filter(p, ColorSpecification(COLOR::GREEN))) { 
    std::cout << item.getName() << " is green\n";
  }

  for(auto& item : BetterFilter().filter(p, SizeSpecification(SIZE::SMALL))) {
    std::cout << item.getName() << " comes in small size\n";
  }

  return 0;
}
