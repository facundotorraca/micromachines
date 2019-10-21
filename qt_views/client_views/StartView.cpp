#include "StartView.h"
#include "ui_startView.h"

StartView::StartView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartView) {
    ui->setupUi(this);
}

StartView::~StartView() {
    delete ui;
}
