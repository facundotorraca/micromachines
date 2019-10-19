#include <QListWidget>
#include "JoinView.h"
#include "ui_joinView.h"

void splitMatchs(std::string input, std::vector<std::string> &match) {
  std::string delimiter = "\n";
  int last = 0;
  int next = input.find(delimiter);
  while (next != std::string::npos) {
    match.push_back(input.substr(last, next));
    last = next;
    next = input.find(delimiter);
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
}

JoinView::~JoinView() {
}
