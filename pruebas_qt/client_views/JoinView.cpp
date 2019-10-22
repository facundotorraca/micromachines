#include <QListWidget>
#include <QVector>
#include <iostream>
#include <QLineEdit>
#include "JoinView.h"
#include "ui_joinView.h"

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

JoinView::JoinView(ProtocolSocket &ps, std::string line_match, QWidget *parent) :
                    QDialog(parent),
                    ps(ps),
                    matches(),
                    ui(),
                    joined(false) {
    ui.setupUi(this);
    splitMatchs(line_match, this->matches);
    QListWidget *matchList = findChild<QListWidget*>("matchList");
    for(size_t ind = 0; ind < this->matches.length(); ind++) {
        QString match = this->matches.at(ind);
        size_t last_char_pos = match.size() - 1;
        QChar last_char = match.at(last_char_pos);
        match.chop(1);
        matchList->addItem(match);
        if (last_char == '1') {
            matchList->item(ind)->setTextColor(QColor(255,0,0));
        }
    }
}

bool JoinView::is_joined() {
    return this->joined;
}

void JoinView::on_matchList_itemSelectionChanged() {
    std::cout<<"CAMBIO LA SELECIONN\n";
    QDialogButtonBox *box = findChild<QDialogButtonBox *>("btnBoxJoin");
    QListWidget *matchList = findChild<QListWidget*>("matchList");
    QColor color = matchList->selectedItems()[0]->textColor();
    if(color == QColor(255,0,0)) {
        box->setDisabled(true);
    } else {
        box->setDisabled(false);
    }
}
void JoinView::on_btnBoxJoin_accepted() {
    QLabel *errorLabel = findChild<QLabel*>("errorLabel");
    QListWidget *matchList = findChild<QListWidget*>("matchList");
    uint8_t flag_error_matchname = 1;
    std::string selectedMatch = matchList->selectedItems()[0]->text().toStdString();
    std::string match_name = selectedMatch.substr(0, selectedMatch.find(" "));
    ps.send(match_name);
    ps.receive(flag_error_matchname);
    uint8_t flag_error_username = 1;
    QLineEdit *usrTxtIn = findChild<QLineEdit*>("usrTxtIn");
    std::string username = usrTxtIn->text().toStdString();
    ps.send(username);
    ps.receive(flag_error_username);
    if(flag_error_username == 1) {
        errorLabel->setText("El nombre de usuario ya esta en uso");
    } else {
        this->joined = true;
        this->close();
    }
}

JoinView::~JoinView() {
}
