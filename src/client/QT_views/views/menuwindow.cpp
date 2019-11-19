#include "menuwindow.h"
#include <client/QT_views/ui_menuwindow.h>
#include <common/SocketError.h>
#include <common/MsgTypes.h>
#include <iostream>
#include <QTimer>

std::string get_matches(ProtocolSocket &ps) {
    std::string matches(1024, '\0');
    ps.receive(matches);
    return matches;
}

void splitMatchs(std::string input, QStringList &match) {
    std::string delimiter = "\n";
    int last = 0;
    int next = input.find(delimiter);
    while (next != std::string::npos) {
        QString match_name = QString::fromStdString(input.substr(last, next - last));
        match.push_back(match_name);
        last = next +1;
        next = input.find_first_of(delimiter, last);
    }
}

MenuWindow::MenuWindow(ProtocolSocket &ps, QWidget *parent) : QMainWindow(parent),
                                                              ui(),
                                                              ps(ps),
                                                              matches(get_matches(this->ps)),
                                                              arranged(false) {
    ui.setupUi(this);
    ui.errorJoinName->setVisible(false);
    ui.errorMatchName->setVisible(false);
    this->update_matches();
}

bool MenuWindow::is_game_arranged() {
    return arranged;
}

bool MenuWindow::get_bot_check() {
    return this->ui.botBox->isChecked();
}

void MenuWindow::on_createBtn_clicked() {
    this->ps.send((uint8_t) CREATE_COMMAND);
    this->ui.stackedWidget->setCurrentIndex(CREATE_PAGE);
}

void MenuWindow::on_joinBtn_clicked() {
    this->ps.send((uint8_t) JOIN_COMMAND);
    this->ui.stackedWidget->setCurrentIndex(JOIN_PAGE);
}

void MenuWindow::on_quitBtn_clicked(){
    this->close();
}

void MenuWindow::on_matchList_itemSelectionChanged() {
    QColor color = this->ui.matchList->selectedItems()[0]->textColor();
    if(color == QColor(255,0,0)) {
        this->ui.joinBtnBox->setDisabled(true);
    } else {
        this->ui.joinBtnBox->setDisabled(false);
    }
}

void MenuWindow::on_updateBtn_clicked() {
    this->ps.send((uint8_t) MSG_GET_MATCHES);
    this->matches = get_matches(this->ps);
    this->update_matches();
}

void MenuWindow::on_joinBtnBox_accepted() {
    std::string selected_match = this->ui.matchList->selectedItems()[0]->text().toStdString();
    std::string match_name = selected_match.substr(0, selected_match.find(" "));
    std::string user_name = this->ui.userJoinInput->text().toStdString();
    this->set_match_name(match_name);
    if(!this->set_user_name(user_name)) {
        this->ui.errorJoinName->setVisible(true);
        return;
    }
    this->arranged = true;
    this->ui.stackedWidget->setCurrentIndex(WAIT_PAGE);
    QTimer::singleShot(50, this, SLOT(wait_start()));
}

void MenuWindow::on_joinBtnBox_rejected(){
    this->ps.send((uint8_t) MSG_CHANGE_MODE);
    this->ui.stackedWidget->setCurrentIndex(MAIN_PAGE);
}

void MenuWindow::on_createBtnBox_accepted() {
    std::string match_name_raw = this->ui.matchCreateInput->text().toStdString();
    std::string match_name = match_name_raw.substr(0, match_name_raw.find(" "));
    std::string user_name = this->ui.userCreateInput->text().toStdString();
    if(!this->set_match_name(match_name)) {
        this->ui.errorMatchName->setVisible(true);
        return;
    }
    this->set_user_name(user_name);
    this->arranged = true;
    this->ui.stackedWidget->setCurrentIndex(START_PAGE);
}

void MenuWindow::on_createBtnBox_rejected(){
    this->ps.send((uint8_t) MSG_CHANGE_MODE);
    this->ui.stackedWidget->setCurrentIndex(MAIN_PAGE);
}

void MenuWindow::on_startBtn_clicked() {
    uint8_t start_game = 1;
    ps.send(start_game);
    uint8_t flag_join_match;
    ps.receive(flag_join_match);
    uint8_t flag_start_match = 1;
    ps.receive(flag_start_match);
    this->close();
}



void MenuWindow::wait_start() {
    std::cout << "ESPERANDO QUE EMPIECE LA PARTIDA" << std::endl;
    uint8_t car = 1;
    ps.send(car);
    uint8_t flag_join_match;
    ps.receive(flag_join_match);
    uint8_t flag_start_match = 1;
    ps.receive(flag_start_match);
    this->close();
}

void MenuWindow::update_matches() {
    QStringList matches_list;
    splitMatchs(this->matches, matches_list);
    for(size_t ind = 0; ind < matches_list.length(); ind++) {
        QString match = matches_list.at(ind);
        size_t last_char_pos = match.size() - 1;
        QChar last_char = match.at(last_char_pos);
        match.chop(1);
        this->ui.matchList->addItem(match);
        if (last_char == '1') {
            this->ui.matchList->item(ind)->setTextColor(QColor(255,0,0));
        }
    }
}

bool MenuWindow::set_user_name(std::string user_name) {
    uint8_t flag_error_username = 1;
    ps.send((uint8_t) MSG_SET_USERNAME);
    ps.send(user_name);
    ps.receive(flag_error_username);
    return flag_error_username == 0;
}

bool MenuWindow::set_match_name(std::string match_name) {
    uint8_t flag_error_matchname = 1;
    ps.send((uint8_t) MSG_SET_MATCH_NAME);
    ps.send(match_name);
    ps.receive(flag_error_matchname);
    return flag_error_matchname == 0;
}

MenuWindow::~MenuWindow() {}