#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(Socket &sck, QWidget *parent)
                      : QMainWindow(parent), ui(), socket(sck) {
  ui.setupUi(this);
}

void MainWindow::on_createMatchBtn_clicked(){
  std::cout<<"CREAR PARTIDA \n";
}

MainWindow::~MainWindow() {}