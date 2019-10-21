#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <common/Socket.h>
#include <common/ProtocolSocket.h>
#include <../qt_views/ui_mainwindow.h>
#include "CreateView.h"
#include "JoinView.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    Ui::MainWindow ui;
    ProtocolSocket &ps;
    std::string matches;
    CreateView create_view;
    JoinView join_view;
 public:
    explicit MainWindow(ProtocolSocket &ps, QWidget *parent = nullptr);
    virtual ~MainWindow();
 private:
 private slots:
    void on_createMatchBtn_clicked();
    void on_joinMatchBtn_clicked();
};

#endif // MAINWINDOW_H
