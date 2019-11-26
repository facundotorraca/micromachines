#include "menuwindow.h"
#include <client/QT_views/ui_menuwindow.h>
#include <common/SocketError.h>
#include <common/MsgTypes.h>
#include <iostream>
#include <QTimer>
#include <QKeyEvent>

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
                                                              arranged(false),
                                                              waiter_worker(this->ps) {
    ui.setupUi(this);
    ui.errorMainLabel->setVisible(false);
    ui.errorJoinLabel->setVisible(false);
    ui.errorCreateLabel->setVisible(false);
    ui.errorStartLabel->setVisible(false);
    this->update_matches();
}

bool MenuWindow::is_game_arranged() {
    return arranged;
}

bool MenuWindow::get_bot_check() {
    return this->ui.botBtn->isChecked();
}

void MenuWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        if (this->ui.stackedWidget->currentIndex() == CREATE_PAGE)
            this->ui.createBtnBox->accepted();
        if (this->ui.stackedWidget->currentIndex() == JOIN_PAGE &&  this->ui.joinBtnBox->button(QDialogButtonBox::Ok)->isEnabled())
            this->ui.joinBtnBox->accepted();
    }
}

void MenuWindow::closeEvent(QCloseEvent *event) {
    if (this->ui.stackedWidget->currentIndex() == START_PAGE && !this->arranged)
        this->ps.send((uint8_t) CANCEL_MATCH);
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
    if (this->ui.matchList->count() == 0 ) {
        return;
    }
    if (this->ui.matchList->selectedItems().count() == 0){
        return;
    }
    QColor color = this->ui.matchList->selectedItems()[0]->textColor();
    if(color == QColor(255,0,0)) {
        this->ui.joinBtnBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    } else {
        this->ui.joinBtnBox->button(QDialogButtonBox::Ok)->setDisabled(false);
    }
}

void MenuWindow::on_updateBtn_clicked() {
    this->ps.send((uint8_t) MSG_GET_MATCHES);
    try {
        this->matches = get_matches(this->ps);
        this->update_matches();
    } catch (SocketError &error) {
        this->ui.stackedWidget->setCurrentIndex(ERROR_SERVER_PAGE);
    }
}

void MenuWindow::on_joinBtnBox_accepted() {
    if (this->ui.matchList->selectedItems().length() == 0 || this->ui.userJoinInput->text().isEmpty())
        return;
    std::string selected_match = this->ui.matchList->selectedItems()[0]->text().toStdString();
    std::string match_name = selected_match.substr(0, selected_match.find(" "));
    std::string user_name = this->ui.userJoinInput->text().toStdString();
    try {
        this->set_match_name(match_name);
        if(!this->set_user_name(user_name)) {
            this->ui.errorJoinLabel->setVisible(true);
            return;
        }
    } catch (SocketError &error) {
        this->ui.stackedWidget->setCurrentIndex(ERROR_SERVER_PAGE);
        return;
    }
    this->ui.stackedWidget->setCurrentIndex(WAIT_PAGE);
    this->waiter_worker.moveToThread(&wait_thread);
    connect(&this->wait_thread, SIGNAL(started()), &this->waiter_worker, SLOT(wait_response()));
    connect(&this->waiter_worker, SIGNAL(resultReady(int)), this, SLOT(handle_wait(int)));
    this->wait_thread.start();
    //QTimer::singleShot(50, this, SLOT(wait_start()));
}

void MenuWindow::on_joinBtnBox_rejected(){
    this->ps.send((uint8_t) MSG_CHANGE_MODE);
    this->ui.stackedWidget->setCurrentIndex(MAIN_PAGE);
}

void MenuWindow::on_createBtnBox_accepted() {
    if (this->ui.matchCreateInput->text().isEmpty() || this->ui.userCreateInput->text().isEmpty())
        return;
    std::string match_name_raw = this->ui.matchCreateInput->text().toStdString();
    std::string match_name = match_name_raw.substr(0, match_name_raw.find(" "));
    std::string user_name = this->ui.userCreateInput->text().toStdString();
    try {
        if(!this->set_match_name(match_name)) {
            this->ui.errorCreateLabel->setVisible(true);
            return;
        }
        this->set_user_name(user_name);
    } catch (SocketError &error) {
        this->ui.stackedWidget->setCurrentIndex(ERROR_SERVER_PAGE);
        return;
    }
    this->ui.stackedWidget->setCurrentIndex(START_PAGE);
}

void MenuWindow::on_createBtnBox_rejected(){
    this->ps.send((uint8_t) MSG_CHANGE_MODE);
    this->ui.stackedWidget->setCurrentIndex(MAIN_PAGE);
}

void MenuWindow::on_startBtn_clicked() {
    try {
        ps.send((uint8_t) START_MATCH);
        uint8_t flag_join_match;
        ps.receive(flag_join_match);
        uint8_t flag_start_match = BAD_FLAG;
        ps.receive(flag_start_match);
        ps.send((uint8_t)GOOD_FLAG);
        this->arranged = true;
        this->close();
    } catch (SocketError &error) {
        this->ui.stackedWidget->setCurrentIndex(ERROR_SERVER_PAGE);
    }
}

void MenuWindow::handle_wait(int result) {
    std::cout << result << std::endl;
    if (result == START_MATCH) {
        this->ps.send(START_MATCH);
        this->arranged = true;
        this->close();
    } else if (result == CLOSE_CONNECTION) {
        this->ui.stackedWidget->setCurrentIndex(ERROR_SERVER_PAGE);
    } else {
        this->ui.waitLabel->setText("EL CREADOR DE LA PARTIDA CERRO EL JUEGO");
    }
};


void MenuWindow::update_matches() {
    this->ui.matchList->clear();
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
    uint8_t flag_error_username = BAD_FLAG;
    ps.send((uint8_t) MSG_SET_USERNAME);
    ps.send(user_name);
    ps.receive(flag_error_username);
    return flag_error_username == GOOD_FLAG;
}

bool MenuWindow::set_match_name(std::string match_name) {
    uint8_t flag_error_matchname = BAD_FLAG;
    ps.send((uint8_t) MSG_SET_MATCH_NAME);
    ps.send(match_name);
    ps.receive(flag_error_matchname);
    return flag_error_matchname == 0;
}


MenuWindow::~MenuWindow() {
    this->wait_thread.quit();
    this->wait_thread.wait();
}
