#include "mywidget.h"

constexpr uint8_t UI_SPACING = 5;

MyWidget::MyWidget(QWidget* parent) :
  QWidget(parent) {

    auto* vLayoutBox = gsl::owner<QVBoxLayout*>(new QVBoxLayout());
    vLayoutBox->setSpacing(UI_SPACING);

    textEdit = gsl::owner<QTextEdit*>(new QTextEdit("Hello World!"));
    vLayoutBox->addWidget(textEdit, 0);
    connect(textEdit, &QTextEdit::textChanged, this, &MyWidget::onTextChanged);

    auto* hLayoutBox = gsl::owner<QHBoxLayout*>(new QHBoxLayout());
    hLayoutBox->setSpacing(UI_SPACING);
    vLayoutBox->addLayout(hLayoutBox);
    
    auto* quitButton = gsl::owner<QPushButton*>(new QPushButton("Quit"));
    hLayoutBox->addWidget(quitButton, 0, Qt::AlignCenter | Qt::AlignBottom);
    connect(quitButton, &QPushButton::clicked, this, &MyWidget::onQuitButtonClicked);

    auto* saveButton = gsl::owner<QPushButton*>(new QPushButton("Save"));
    hLayoutBox->addWidget(saveButton, 0, Qt::AlignCenter | Qt::AlignBottom);
    connect(saveButton, &QPushButton::clicked, this, &MyWidget::onSaveButtonClicked);
    this->setLayout(vLayoutBox);

    std::ifstream in("output.txt");
    if(in) {
      std::stringstream str;
      str << in.rdbuf(); //read the file
      textEdit->setText(str.str().c_str());
    }
  }

void MyWidget::keyPressEvent(QKeyEvent* event) {
  if(event->key() == Qt::Key_Escape) {
    qApp->quit(); //NOLINT
  }
}

void MyWidget::onQuitButtonClicked() {
  std::clog << "Quit button clicked!\n";

  qApp->quit(); // NOLINT
}

void MyWidget::onSaveButtonClicked() {
  auto text = textEdit->toPlainText().toStdString();

  std::ofstream out("output.txt");
  out << text;
}

void MyWidget::onTextChanged() {

}

