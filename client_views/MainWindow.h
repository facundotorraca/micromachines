#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <common/Socket.h>

class MainWindow : public QMainWindow {
 Q_OBJECT
  Ui::MainWindow ui;
  Socket &socket;
 public:
  explicit MainWindow(Socket &sck, QWidget *parent = nullptr);
  virtual ~MainWindow();
 private slots:
  void on_createMatchBtn_clicked();
};

#endif // MAINWINDOW_H
