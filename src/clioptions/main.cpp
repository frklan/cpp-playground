#include <boost/program_options.hpp>
#include <iostream>
#include <string> 

const size_t ERROR_IN_COMMAND_LINE = 1; 
const size_t SUCCESS = 0; 

class App {
  public:
    App() = delete;
    App(int argc, char** argv);

    void run();

  private:
    bool isAbsoluteTime = true;
    std::string time;
};

App::App(int argc, char** argv) {

  // Define and parse the program options  
  namespace po = boost::program_options; 
  po::options_description desc("Options"); 
  desc.add_options() 
    ("help", "Print help messages") 
    (",d", "use delta time") 
    ("time", po::value<std::string>(&time)->required(), "alarm time");
  
  po::positional_options_description positionalOptions; 
  positionalOptions.add("time", 1); 

  po::variables_map vm; 
  try { 
    po::store(po::command_line_parser(argc, argv).options(desc).positional(positionalOptions).run(), vm);

    if(vm.count({"help"}) != 0) { 
      std::cout << "Basic Command Line Parameter App" << std::endl << desc << std::endl; 
      exit(SUCCESS); 
    } 
    if(vm.count({"-d"}) != 0) {
     isAbsoluteTime = false;
    }
    po::notify(vm); // throws on error, so do after help in case there are any problems 

  } catch(po::error& e) { 
    std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
    std::cerr << desc << std::endl;
    exit(ERROR_IN_COMMAND_LINE);
  } 
}

void App::run() {
  std::cout << "app is running!!" << '\n';
  std::cout << "time is: " << time << '\n';
  std::cout  << "we're in " << (isAbsoluteTime ? "absolute " : "delta ") << "mode" << std::endl;
}

int main(int argc, char** argv) {
  std::cout << "<-- CLI options -->\n";

  App app{argc, argv};
  app.run();
}
