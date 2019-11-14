#include "WaitView.h"
#include <iostream>
#include <client/QT_views/ui_waitView.h>
#include <common/ProtocolSocket.h>

WaitView::WaitView(ProtocolSocket &ps, QWidget *parent) :
    QDialog(parent),
    ps(ps),
    ui() {
    ui.setupUi(this);
}

void WaitView::show(){
    QDialog::show();
    QApplication::processEvents();
}

void WaitView::on_waitBtn_clicked(){
    QPushButton *waitBtn = findChild<QPushButton*>("waitBtn");
    waitBtn->setDisabled(true);
    waitBtn->setEnabled(false);
    std::cout << "Waiting for the game to START \n";
    uint8_t car = 1;
    ps.send(car);

    uint8_t flag_join_match;
    ps.receive(flag_join_match);
    std::cout << "Flag JOIN: " << unsigned(flag_join_match) << "\n";

    uint8_t flag_start_match = 1;
    ps.receive(flag_start_match);
    this->done(flag_start_match);
}

WaitView::~WaitView() {}
