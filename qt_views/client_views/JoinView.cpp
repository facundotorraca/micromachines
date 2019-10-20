#include <QListWidget>
#include <QVector>
#include <iostream>
#include "JoinView.h"
#include "ui_joinView.h"

void splitMatchs(std::string input, QStringList &match) {
  std::string delimiter = "\n";
  int last = 0;
  int next = input.find(delimiter);
  while (next != std::string::npos) {
    match.push_back(QString::fromStdString(input.substr(last, next - last)));
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
  matchList->addItems(this->matches);
}

void JoinView::on_btnBoxJoin_accepted() {
  QListWidget *matchList = findChild<QListWidget*>("matchList");
  std::string selectedMatch = matchList->selectedItems()[0]->text().toStdString();
  std::cout << "Me uno a " << selectedMatch << "\n";
}

JoinView::~JoinView() {
}
