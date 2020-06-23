#pragma once

#include <QWidget>
#include "ui_mywidget.h"

class MyWidget: public QWidget {
  Q_OBJECT

  public:
    MyWidget(QWidget* parent = nullptr);
    ~MyWidget();

  private:
    Ui::MainWindow *ui;
};

