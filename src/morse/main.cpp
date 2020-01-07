#include <functional>
#include <iostream>
#include <map>
#include <vector>


class MorseEncoder {
  public: 
    void dashCb() { std::clog << "-"; }
    void dotCb() { std::clog << "."; }

  public:
    MorseEncoder() {
      setDash(std::bind(&MorseEncoder::dashCb, this));
      setDot(std::bind(&MorseEncoder::dotCb, this));

      setEncoder();
    }

    void encode(const std::string& input) {
      std::clog << "encoding: " << input << '\n';

      for_each(input.begin(), input.end(), [&](auto& ch){
        std::clog << ch << ": ";
        for(auto& cb : encoder[ch]) {
          cb();
        }
        std::clog << '\n';
      });

    }

    void setDash(const std::function<void()>& f) { 
      this->dash = f; 
      setEncoder();
    } 
    void setDot(const std::function<void()>& f) { 
      this->dot = f;
      setEncoder();
    }

  private:
    void setEncoder() {
      encoder['a'] = {dot, dash};
      encoder['b'] = {dash, dot, dot, dot};
      encoder['c'] = {dash, dot, dash, dot};
      encoder['d'] = {dash, dot, dot};
      encoder['e'] = {dot};
      encoder['f'] = {dot, dot, dash, dot};
      encoder['g'] = {dash, dash, dot};
      encoder['h'] = {dot, dot, dot, dot};
      encoder['i'] = {dot, dot};
      encoder['j'] = {dot, dash, dash, dash};
      encoder['k'] = {dash, dot, dash};
      encoder['l'] = {dot, dash, dot, dot};
      encoder['m'] = {dash, dash};
      encoder['n'] = {dash, dot};
      encoder['o'] = {dash, dash, dash};
      encoder['p'] = {dot, dash, dash, dot};
      encoder['q'] = {dash, dash, dot, dash};
      encoder['r'] = {dot, dash, dot};
      encoder['s'] = {dot, dot, dot};
      encoder['t'] = {dash};
      encoder['u'] = {dot, dot, dash};
      encoder['v'] = {dot, dot, dot, dash};
      encoder['w'] = {dot, dash, dash};
      encoder['x'] = {dash, dot, dot, dash};
      encoder['y'] = {dash, dot, dash, dash};
      encoder['z'] = {dash, dash, dot, dot};
    }

    std::function<void()> dash;
    std::function<void()> dot;

    std::map<char, std::vector<std::function<void()>> > encoder;
};


void mydot() { std::clog << '\''; }
void mydash() { std::clog << '*'; }

int main(int /* unused */ , char** /* unused */) {
  try {
    MorseEncoder me;
    me.encode("hello world!");

    me.setDash([](){ std::clog << '/'; });
    me.setDot([](){ std::clog << '|'; });
    me.encode("hello world!");
   
    me.setDash(std::bind(mydash));
    me.setDot(std::bind(mydot));
    me.encode("hello world!");
  } catch(std::exception& e) {
    std::cerr << e.what();
  }

  return 0;
}

