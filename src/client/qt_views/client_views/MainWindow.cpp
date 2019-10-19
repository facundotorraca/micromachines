#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <iostream>

std::string get_matches(ProtocolSocket &ps) {
  std::vector<uint8_t> buffer(4096, 1);

  ps.receive(buffer);
  std::string matches(reinterpret_cast<const char *>(buffer.data()), buffer.size());

  std::cout << "#-----------------PARTIDAS EXISTENTES---------------#\n";
  std::cout << matches;
  std::cout << "#---------------------------------------------------#\n";
  return matches;
}


MainWindow::MainWindow(ProtocolSocket &ps, QWidget *parent) : QMainWindow(parent),
                                                              ui(),
                                                              ps(ps),
                                                              matches(get_matches(this->ps)),
                                                              create_view(this->ps) {
  ui.setupUi(this);
}

void MainWindow::on_createMatchBtn_clicked(){
  std::cout << "CREAR PARTIDA \n";
  uint8_t start = 2;
  this->ps.send(start);
  this->create_view.show();
  this->close();
}

MainWindow::~MainWindow() {}


