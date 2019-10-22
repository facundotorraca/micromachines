#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <common/Socket.h>
#include <common/ProtocolSocket.h>
#include <../qt_views/ui_mainwindow.h>
#include "CreateView.h"
#include "JoinView.h"
#include "StartView.h"
#include "WaitView.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    Ui::MainWindow ui;
    ProtocolSocket &ps;
    std::string matches;
    CreateView create_view;
    JoinView join_view;
    StartView start_view;
    WaitView wait_view;
    bool fixed;
 public:
    explicit MainWindow(ProtocolSocket &ps, QWidget *parent = nullptr);
    bool is_fixed();
    virtual ~MainWindow();
 private:
 private slots:
    void on_createMatchBtn_clicked();
    void on_joinMatchBtn_clicked();
};

#endif // MAINWINDOW_H
