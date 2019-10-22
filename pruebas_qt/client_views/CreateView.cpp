#include <iostream>
#include <QLineEdit>
#include "CreateView.h"
#include "ui_createView.h"

CreateView::CreateView(ProtocolSocket &ps, QWidget *parent) :
                        QDialog(parent),
                        ps(ps),
                        ui(),
                        created(false){
    ui.setupUi(this);
}

bool CreateView::is_created() {
    return this->created;
}

void CreateView::on_btnBoxCreate_accepted() {
    QLabel *errorLabel = findChild<QLabel*>("errorLabel");
    uint8_t flag_error_matchname = 1;
    QLineEdit *matchTxtIn = findChild<QLineEdit*>("matchTxtIn");
    std::string match_name = matchTxtIn->text().toStdString();
    ps.send(match_name);
    ps.receive(flag_error_matchname);
    if(flag_error_matchname != 0) {
      errorLabel->setText("El nombre de la partida ya esta en uso");
      return;
    }
    uint8_t flag_error_username = 1;
    QLineEdit *usrTxtIn = findChild<QLineEdit*>("usrTxtIn");
    std::string username = usrTxtIn->text().toStdString();
    ps.send(username);
    ps.receive(flag_error_username);
    this->created = true;
    this->close();
}

CreateView::~CreateView() {}
