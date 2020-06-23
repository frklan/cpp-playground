#include "mywidget.h"

MyWidget::MyWidget(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::MainWindow) {

    ui->setupUi(this);
  }


MyWidget::~MyWidget() {
  delete ui;
}

