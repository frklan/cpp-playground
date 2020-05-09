#include <iostream>
#include <memory>
#include <string>

class Widget {
  public:
    Widget() { 
      std::clog << "Widget::Widget() (default constructor)\n"; 

      i = std::make_unique<int>(1);
    }

    explicit Widget(const std::string& n) :
    name(n)
    {
      std::clog << "Widget::Widget(const std::string)\n";
      i = std::make_unique<int>(2);
    }

    
    ~Widget() { 
      std::clog << "Widget::~Widget() (default destructor)\n"; 
    }
    
    // copy constructor
    Widget(const Widget& w) noexcept { 
      i = std::make_unique<int>(3);
      this->name = "copied from " + w.name;
      std::clog << "Widget::Widget(Widget&) (copy constructor @ " << this->name << ")\n";
    }
    
    // copy assign
    Widget& operator=(const Widget& rhs) noexcept {
      i = std::make_unique<int>(4);
      this->name = "copy assigned from " + rhs.name;
      std::clog << "Wdiget& operator=(const Widget&) noexcept (copy assignment @ " << this->name << "))\n";

      if(this == &rhs) {}
      return *this;
    }

    // move constructor
    Widget(Widget&& rhs) noexcept { 
      i = std::make_unique<int>(5);
      this->name = "moved from " + rhs.name;
      std::clog << "Widget::Widget(Widget&&) (move constructor @ " << this->name << "))\n"; }
    
    // move assign
    Widget& operator=(Widget&& rhs) noexcept {
      i = std::make_unique<int>(6);
      this->name = "move assigned from " + rhs.name;
      std::clog << "Wdiget& operator=(Widget&&) noexcept (move assignment @ " << this->name << "))\n";
      return *this;
    }



    void work() {
      std::clog << "doing work on " << this->name << " i = " << std::to_string(*i) << '\n';
    }

  private:
    std::string name = "";
    std::unique_ptr<int> i;

};

void useWidget(std::shared_ptr<Widget> w) {
  std::clog << "in UseWidget(std::shared_ptr<Widget>)\n";
    std::clog << "calling Widget::work()\n";
    w->work();
}

std::shared_ptr<Widget> make_widget(const std::string& n) {
  return std::make_shared<Widget>(n);
}

Widget stack_widget() {
  Widget w("stack_widget()");
  return w;
}

Widget& stack_widget_ref() {
  Widget w("stack widget as ref");
  return w;
}

int main(int /*argc*/, char** /*argv*/)
{
  std::clog << "<-- object passing -->\n";

  std::clog << "\n\n";
  {
    std::clog << "creating Widget on the stack\n";
    Widget w("w");
    
    std::clog << "calling Widget::work()\n";
    w.work();
  }


  std::clog << "\n\n";
  {
    std::clog << "Creating on w1 stack\n";
    Widget w1("w1");
    std::clog << "calling Widget::work()\n";
    w1.work();

    std::clog << "Creating w2{w1}\n";
    Widget w2{w1};
    std::clog << "calling Widget::work()\n";
    w2.work();

    std::clog << "creating w3\n";
    Widget w3("w3");
    std::clog << "calling Widget::work()\n";
    w3.work();

    std::clog << "assigning w3 = w1\n";
    w3 = w1;
    std::clog << "calling Widget::work()\n";
    w3.work();
  }

  std::clog << "\n\n";
  {
    std::clog << "creating w = std::shared_ptr<Widget>\n";
    auto w = std::make_shared<Widget>("shared w");
    
    std::clog << "calling Widget::work()\n";
    w->work();

    std::clog << "passing w to function\n";
    useWidget(w);
  }

  std::clog << "\n\n";
  {
    std::clog << "using make_widget()\n";
    auto w = make_widget("w = make_widget()");
    
    std::clog << "calling w->work()\n";
    w->work();
  }

  std::clog << "\n\n";
  {
    std::clog << "using stack_widget()\n";
    auto w = stack_widget();

    std::clog << "calling w->work()\n";
    w.work();
  }

  std::clog << "\n\n";
  {
    std::clog << "using stack_widget_ref()\n";
    auto w = stack_widget_ref();

    std::clog << "calling w->work()\n";
    w.work();
  }

  return 0;
}
