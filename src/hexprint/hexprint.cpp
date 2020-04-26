#include <fstream>
#include <iostream>
#include <vector>

constexpr int64_t LINE_LENGHT = 16;
constexpr char MIN_PRINTABLE = 32;
constexpr char MAX_PRINTABLE = 127;

int main(int  argc, char** argv) {
  auto args = std::vector<std::string>(argv, argv + argc); //NOLINT
  
  if(args.size() != 2) {
    std::cerr << "Use:\n" << "  hexprint [file]\n";
    exit(-1);
  }
  
  const std::string filename = args[1];
  std::ifstream file;

  try {
    file.open(filename, std::ios::binary);
    if(!file){
      std::cerr << "Unable to open file '" << filename << "'\n";
      exit(-2);
    }

    uint8_t c = 0;
    int64_t i = 0;
    std::string ascii;

    while(file >> c) {
      
      if(i % LINE_LENGHT == 0) {
        std::clog << "    " << ascii;
        ascii.clear();
        
        std::clog << "\n0x" << std::setw(2) << std::setfill('0')
          << std::hex << i << ": ";
      }
      std::clog << "0x" << std::setw(2) << std::setfill('0') 
        << std::hex << static_cast<int>(c) << ' ';
      if(c >= MIN_PRINTABLE && c <= MAX_PRINTABLE) {
        ascii.push_back(c);
      } else {
        ascii.push_back('.');
      }
      i++;
    }
    std::clog << std::endl;
    
    file.close();
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    std::abort();
  }
  return 0;
}
