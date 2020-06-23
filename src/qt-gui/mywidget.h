#pragma once

#include <memory>
#include <QApplication>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QTableView>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <fstream>
#include <istream>
#include <iostream>
#include <sstream>
#include <gsl/gsl>

class MyWidget: public QWidget {

  public:
    MyWidget(QWidget* parent = nullptr);

  protected:
    virtual void keyPressEvent(QKeyEvent* e) override;

    static void onQuitButtonClicked();
    void onSaveButtonClicked();
    void onTextChanged();

  private:
    gsl::owner<QTextEdit*> textEdit;
};

