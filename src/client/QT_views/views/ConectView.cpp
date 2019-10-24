#include "ConectView.h"
#include <iostream>
#include <string>
#include <QtWidgets/QLineEdit>
#include <common/SocketError.h>
#include <client/qt_views/ui_conectview.h>


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
    try {
      this->socket.connect(ipTxt,serviceTxt);
    } catch (SocketError &e) {
      QLabel *errorLabel = findChild<QLabel*>("errorLabel");
      errorLabel->setText("Algo fallo en la conexion intentelo de nuevo");
      return;
    }
    this->close();
}

ConectView::~ConectView() {}
