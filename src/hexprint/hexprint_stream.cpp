#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

static std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t>& data) {
  for(size_t i = 0; i < data.size(); i++) {
    if(i % 16 == 0) {
      os << "\n0x" << std::setw(2) << std::setfill('0')
        << std::hex << i << ": ";
    }
    os << "0x" << std::setw(2) << std::setfill('0') 
      << std::hex << static_cast<unsigned int>(data[i]) << ' ';
  }
  os << '\n';

  return os;
}
  
  
int main(int  argc, char** argv) {

  if(argc != 2) {
    std::cerr << "No input file specified\n";
    return -1;
  }
  
  const std::string filename{argv[1]};
  std::ifstream file;
  file.open(filename, std::ios::binary);
  if(!file){
    std::cerr << "Unable to open file '" << filename << "'\n";
    exit(-1);
  }

  uint8_t c = ' ';
  long i = 0;
  std::string ascii;
  while(file >> c) {
    if(i % 16 == 0) {
      std::clog << "    " << ascii;
      ascii.clear();
      
      std::clog << "\n0x" << std::setw(2) << std::setfill('0')
        << std::hex << i << ": ";
    }
    std::clog << "0x" << std::setw(2) << std::setfill('0') 
      << std::hex << static_cast<unsigned int>(c) << ' ';
    if(c > 31 && c < 127 ) {
      ascii += c;
    } else {
      ascii += ".";
    }
    i++;
  }
  std::clog << std::endl;
  
  file.close();
  return 0;

  /*
  std::clog << "input.size = " << input.size() << '\n';

  std::clog << "input was:\n" << input << '\n';

  return 0;
  const std::vector<uint8_t> numbers{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::clog << "Outputting 'numbers' vector\n" << numbers << '\n';

  const std::vector<uint8_t> hello = {'h','e','l','l','o',' ','w','o','r','l','d'};
  std::clog << "Ouputing 'hello' vector\n" << hello << '\n';
  
  return 0;
  */
}
