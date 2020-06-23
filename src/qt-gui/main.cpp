#include <QApplication>

#include "mywidget.h"

constexpr uint16_t HEIGHT = 640;
constexpr uint16_t WIDTH = 800;


int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  
  MyWidget window;

  window.resize(WIDTH, HEIGHT);
  window.setWindowTitle("Simple example");
  window.show();

  return QApplication::exec();
}
