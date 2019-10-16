#include "newmatchview.h"
#include "ui_newmatchview.h"

NewMatchView::NewMatchView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewMatchView)
{
    ui->setupUi(this);
}

NewMatchView::~NewMatchView()
{
    delete ui;
}
