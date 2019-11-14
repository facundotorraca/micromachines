#include "StartView.h"
#include <client/QT_views/ui_startView.h>
#include <iostream>

StartView::StartView(ProtocolSocket &ps, QWidget *parent) :
    QDialog(parent),
    ps(ps),
    ui() {
    ui.setupUi(this);
}

void StartView::on_startBtn_clicked() {
    std::string welcome_message(100, '\0');
    std::cout << "Press any key to START" << "\n";
    uint8_t start_game = 1;
    ps.send(start_game);

    uint8_t flag_join_match;
    ps.receive(flag_join_match);
    std::cout << "Flag JOIN: " << unsigned(flag_join_match) << "\n";

    uint8_t flag_start_match = 1;
    ps.receive(flag_start_match);
    this->done(flag_start_match);
}

StartView::~StartView() {
}
