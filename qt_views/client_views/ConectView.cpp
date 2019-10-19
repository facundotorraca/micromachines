#include "ConectView.h"
#include <iostream>
#include <string>
#include <QtWidgets/QPlainTextEdit>

ConectView::ConectView(Socket &sck, QWidget *parent)
                      : QDialog(parent), ui(), socket(sck){
  ui.setupUi(this);
}

void ConectView::on_btnBox_accepted() {
  QPlainTextEdit *ipTextEdit = findChild<QPlainTextEdit*>("IPTxtIn");
  QPlainTextEdit *serviceTextEdit = findChild<QPlainTextEdit*>("ServiceTxtIn");
  std::string ipTxt = ipTextEdit->toPlainText().toStdString();
  std::string serviceTxt = serviceTextEdit->toPlainText().toStdString();
  std::cout<<ipTxt<<" ; "<<serviceTxt<<"\n";
  this->socket.connect(ipTxt,serviceTxt);
}

ConectView::~ConectView() {
}
