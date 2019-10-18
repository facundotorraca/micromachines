#include "CreateWindow.h"
#include "ui_createWindow.h"

CreateWindow::CreateWindow(QWidget *parent) :
    QMainWindow(parent),
    ui() {
    ui.setupUi(this);
}

CreateWindow::~CreateWindow() {
}
