#include <iostream>
#include <span>

int main(int argc, char** argv) {

  if(argc != 2) {
    std::cerr << "Invalid number of arguments arguments; I require exactly one!\n";
    exit(-1);
  }

  char c = *argv[1];

  switch(c) {
    case 'a':
      std::cout << "a\n";
      break;
    case 'b' ... 'g':
      std::cout << "b ... g\n";
      break;
    case '0' ... '9':
      std::cout << "I got a number!\n";
      break;
    default:
      std::cout << "not handled\n";
  }

  return 0;

}
