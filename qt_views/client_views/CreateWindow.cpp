#include "CreateWindow.h"

CreateWindow::CreateWindow(QWidget *parent) :
    QMainWindow(parent),
    ui() {
    ui.setupUi(this);
}

CreateWindow::~CreateWindow() {
}
