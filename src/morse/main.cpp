#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>
#include <sstream>
#include <thread>
#include <vector>


/* ********************************************
 * a dot is one unit long
 * a dash is three units long
 * space between dash and dot is one unit long
 * space between characters is three units
 * space between words is seven units
 * ******************************************** */
class MorseEncoder {
  public:
    MorseEncoder() {
      setEncoder();
    }

    [[nodiscard]]
    std::chrono::microseconds getDotLenght() const { return this->dotLenght; }
    constexpr void setDotLenght(const std::chrono::microseconds lenght) { this->dotLenght = lenght; }

    void encode(const std::string& input) {
      auto message = cleanMessage(input);
      auto words = splitIntoWords(message);

      messageStart(input);
      for_each(words.begin(), words.end(), [&](auto word) {
        wordStart(word);
        for_each(word.begin(), word.end(), [&](auto character){
          characterStart(character);
          for(auto& cb : encoder[character]) {
            cb();
          }
          characterEnd();
        });
        wordEnd();
      });
      messageEnd();
    }

    void setDash(const std::function<void()>& f) { 
      this->dash = f; 
      setEncoder();
    }

    void setDot(const std::function<void()>& f) { 
      this->dot = f;
      setEncoder();
    }
    
    void setMessageStart(const std::function<void(const std::string message)>& f) {
      this->messageStart = f;
    }

    void setMessageEnd(const std::function<void()>& f) {
      this->messageEnd = f;
    }

    void setWordStart(const std::function<void(const std::string word)>& f){
    this->wordStart = f;
    }

    void setWordEnd(const std::function<void()>& f) {
    this->wordEnd = f;
    }

    void setCharacterStart(const std::function<void(const unsigned char)>& f) {
      this->characterStart = f;
    }

    void setCharaterEnd(const std::function<void()>& f) {
      this->characterEnd = f;
    }

  protected:
    void delay(const uint8_t numOfDots) {
      std::this_thread::sleep_for(numOfDots * this->dotLenght);
    }

    /* Replace any non alpha numeric characters with a space */
    static std::string cleanMessage(const std::string& input) {
      std::regex filter("[^a-zA-Z0-9]");
     
      std::string cleanedString;
      std::regex_replace(std::back_inserter(cleanedString), input.begin(), input.end(), filter, " ");
     
      std::transform(cleanedString.begin(), cleanedString.end(), cleanedString.begin(), 
          [](unsigned char ch) -> char { return static_cast<char>(std::tolower(static_cast<unsigned char>(ch))); });
      
      return cleanedString;
    }

    /* Split input message into a vector of words, excluding spaces */
    static std::vector<std::string> splitIntoWords(const std::string& input) {
      std::string tmp; 
      std::stringstream str_strm(input);
      std::vector<std::string> words; 
      while (str_strm >> tmp) {
        words.push_back(tmp);
      }
     
      return words;
    }

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
      encoder['1'] = {dot, dash, dash, dash, dash};
      encoder['2'] = {dot, dot, dash, dash, dash};
      encoder['3'] = {dot, dot, dot, dash, dash};
      encoder['4'] = {dot, dot, dot, dot, dash};
      encoder['5'] = {dot, dot, dot, dot, dot};
      encoder['6'] = {dash, dot, dot, dot, dot};
      encoder['7'] = {dash, dash, dot, dot, dot};
      encoder['8'] = {dash, dash, dash, dot, dot};
      encoder['9'] = {dash, dash, dash, dash, dot};
      encoder['0'] = {dash, dash, dash, dash, dash};
    }

  private:
    std::chrono::microseconds dotLenght = std::chrono::microseconds(0);
    std::map<char, std::vector<std::function<void()>> > encoder;

    std::function<void()> dash = [](){ std::clog << "-"; };
    std::function<void()> dot = [](){ std::clog << "."; };
    std::function<void(const std::string&)> messageStart = [](const std::string& message){ std::clog << "Transmission starts\nMessage is: \"" << message  << "\"\n";}; 
    std::function<void()> messageEnd = [](){ std::clog << "\n\nTransmission done.\n"; };
    std::function<void(const std::string&)> wordStart = [](const std::string& /* unused */ ){ };
    std::function<void()> wordEnd = [](){ std::clog << ' '; };
    std::function<void(const char ch)> characterStart = [](unsigned char /*unused */ ){ };
    std::function<void()> characterEnd = [](){ std::clog << ' '; };
};

int main(int /* unused */ , char** /* unused */) {
  try {
    MorseEncoder me;
    me.encode("Hello World. Welcome to this morse encoder");
  } catch(std::exception& e) {
    std::cerr << e.what();
  }

  return 0;
}

