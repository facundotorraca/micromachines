#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <common/socket.h>
#include <common/ProtocolSocket.h>
#include <client/qt_views/ui_mainwindow.h>
#include "CreateView.h"

class MainWindow : public QMainWindow {
 Q_OBJECT
  Ui::MainWindow ui;
  ProtocolSocket &ps;
  std::vector<std::string> matches;
  CreateView create_view;
 public:
  explicit MainWindow(ProtocolSocket &ps, QWidget *parent = nullptr);
  virtual ~MainWindow();
 private:
 private slots:
  void on_createMatchBtn_clicked();
};

#endif // MAINWINDOW_H
