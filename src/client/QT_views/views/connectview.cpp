#include "connectview.h"
#include <common/SocketError.h>

ConnectView::ConnectView(Socket &sck, QWidget *parent) : QDialog(parent),
                                                        ui(), socket(sck) {
    ui.setupUi(this);
    this->ui.errorLabel->setVisible(false);
}

void ConnectView::on_connectionBtnBox_accepted() {
    if(this->ui.ipInput->text().isEmpty() || this->ui.serviceInput->text().isEmpty())
        return;
    auto ip = this->ui.ipInput->text().toStdString();
    auto service = this->ui.serviceInput->text().toStdString();
    try {
        this->socket.connect(ip,service);
    } catch (SocketError &e) {
        this->ui.errorLabel->setVisible(true);
        return;
    }
    this->close();
}

void ConnectView::on_connectionBtnBox_rejected() {
    this->close();
}

ConnectView::~ConnectView() {}
