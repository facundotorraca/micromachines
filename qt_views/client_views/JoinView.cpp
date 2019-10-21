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
                    ui() {
  ui.setupUi(this);
  splitMatchs(line_match, this->matches);
  QListWidget *matchList = findChild<QListWidget*>("matchList");
  for(size_t ind = 0; ind < this->matches.length(); ind++) {
      QString match = this->matches.at(ind);
      size_t last_char_pos = match.size() - 1;
      QChar last_char = match.at(last_char_pos);
      matchList->addItem(match);
      if (last_char == '1') {
          matchList->item(ind)->setTextColor(QColor(255,0,0));
      }
  }
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
    QListWidget *matchList = findChild<QListWidget*>("matchList");
    std::vector<uint8_t> buffer(4096);
    std::string server_match_answer("ERROR");
    while (server_match_answer.substr(0,5) == "ERROR") {
        std::cout << "Write match name..." << "\n";
        std::string selectedMatch = matchList->selectedItems()[0]->text().toStdString();
        std::string match_name = selectedMatch.substr(0, selectedMatch.find(" "));
        std::cout << "Me uno a " << match_name << "\n";
        ps.send(match_name);
        ps.receive(buffer);
        server_match_answer.assign(reinterpret_cast<const char *>(buffer.data()), buffer.size());
        buffer.clear(); buffer.resize(4096);
        std::cout << server_match_answer;
    }

    std::string server_username_answer("ERROR");
    while (server_username_answer.substr(0,5) == "ERROR") {
        std::cout << "Write your username..." << "\n";
        QLineEdit *usrTxtIn = findChild<QLineEdit*>("usrTxtIn");
        std::string username = usrTxtIn->text().toStdString();
        std::cout << "EL usuario " << username << "\n";
        ps.send(username);
        ps.receive(buffer);
        server_username_answer.assign(reinterpret_cast<const char *>(buffer.data()), buffer.size());
        buffer.clear(); buffer.resize(4096);
        std::cout << server_username_answer;
    }
    this->close();
}

JoinView::~JoinView() {
}
