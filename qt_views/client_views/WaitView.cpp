#include "WaitView.h"
#include <iostream>
#include <ui_waitView.h>
#include <common/ProtocolSocket.h>

WaitView::WaitView(ProtocolSocket &ps, QWidget *parent) :
    QDialog(parent),
    ps(ps),
    ui() {
    ui.setupUi(this);
}

void WaitView::wait_start() {
  std::vector<uint8_t> buffer(4096);
  std::cout << "Waiting for the game to START \n";
  uint8_t car = 1;
  ps.send(car);

  bool continue_receiving = true;
  ps.receive(buffer);
  std::string welcome_message(reinterpret_cast<const char *>(buffer.data()), buffer.size());

  std::cout << welcome_message;
  if (welcome_message.substr(0,5) == "ERROR") {
    continue_receiving = false;
  }
  this->close();
}

WaitView::~WaitView() {}
