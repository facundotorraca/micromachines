#include "WaitWindow.h"
#include "ui_WaitWindow.h"

WaitWindow::WaitWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitWindow)
{
    ui->setupUi(this);
}

WaitWindow::~WaitWindow()
{
    delete ui;
}
