#include "ConectView.h"
#include <iostream>
#include <string>
#include <QtWidgets/QLineEdit>

ConectView::ConectView(Socket &sck, QWidget *parent)
                      : QDialog(parent), ui(), socket(sck){
  ui.setupUi(this);
}

void ConectView::on_btnBox_accepted() {
  QLineEdit *ipTextEdit = findChild<QLineEdit*>("IPTxtIn");
  QLineEdit *serviceTextEdit = findChild<QLineEdit*>("ServiceTxtIn");
  std::string ipTxt = ipTextEdit->text().toStdString();
  std::string serviceTxt = serviceTextEdit->text().toStdString();
  std::cout<<ipTxt<<" ; "<<serviceTxt<<"\n";
  this->socket.connect(ipTxt,serviceTxt);
}

ConectView::~ConectView() {
}
