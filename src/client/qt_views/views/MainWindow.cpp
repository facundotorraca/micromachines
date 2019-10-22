#include "MainWindow.h"
#include <iostream>
#include <unistd.h>
#include <client/qt_views/ui_mainwindow.h>


std::string get_matches(ProtocolSocket &ps) {
    std::string matches(1024, '\0');
    ps.receive(matches);
    std::cout << "#-----------------PARTIDAS EXISTENTES---------------#\n";
    std::cout << matches;
    std::cout << "#---------------------------------------------------#\n";
    return matches;
}


MainWindow::MainWindow(ProtocolSocket &ps,
                        QWidget *parent) : QMainWindow(parent),
                                          ui(),
                                          ps(ps),
                                          matches(get_matches(this->ps)),
                                          create_view(this->ps),
                                          join_view(this->ps, this->matches),
                                          start_view(this->ps),
                                          wait_view(this->ps),
                                          fixed(false) {
    ui.setupUi(this);
}

bool MainWindow::is_fixed() {
    return this->fixed;
}

void MainWindow::on_createMatchBtn_clicked(){
    uint8_t start = 2;
    this->ps.send(start);
    this->create_view.show();
    this->create_view.exec();
    if(this->create_view.is_created()) {
        this->close();
        this->start_view.show();
        this->start_view.exec();
        fixed = true;
    }
}

void MainWindow::on_joinMatchBtn_clicked() {
    uint8_t start = 1;
    this->ps.send(start);
    this->join_view.show();
    this->join_view.exec();
    if(this->join_view.is_joined()){
        this->close();
        this->wait_view.open();
        this->wait_view.exec();
        fixed = true;
    }
}

MainWindow::~MainWindow() {}


