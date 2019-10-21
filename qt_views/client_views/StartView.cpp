#include "StartView.h"
#include <ui_startView.h>
#include <iostream>

StartView::StartView(ProtocolSocket &ps, QWidget *parent) :
    QDialog(parent),
    ps(ps),
    ui() {
    ui.setupUi(this);
}

void StartView::on_startBtn_clicked() {
  std::vector<uint8_t> buffer(4096);
  std::cout << "Press any key to START" << "\n";
  uint8_t start_game = 1;
  ps.send(start_game);

  bool continue_receiving = true;
  ps.receive(buffer);
  std::string welcome_message(reinterpret_cast<const char *>(buffer.data()), buffer.size());

  std::cout << welcome_message;
  if (welcome_message.substr(0,5) == "ERROR") {
    continue_receiving = false;
  }
  this->close();
}

StartView::~StartView() {
}
