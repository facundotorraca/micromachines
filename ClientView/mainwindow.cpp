#include "mainwindow.h"
#include "newmatchview.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , newMatchView()
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setAction(void(*callback)(void)){
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createMatchBT_clicked()
{
    this->newMatchView.show();
    this->hide();
}
