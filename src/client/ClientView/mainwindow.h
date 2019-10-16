#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newmatchview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setAction(void(*callback)(void));
    ~MainWindow();

private slots:
    void on_createMatchBT_clicked();

private:
    NewMatchView newMatchView;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
