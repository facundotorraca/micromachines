#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <QMainWindow>
#include <client/qt_views/ui_createWindow.h>

class CreateWindow : public QMainWindow {
    Q_OBJECT
    Ui::CreateWindow ui;
public:
    explicit CreateWindow(QWidget *parent = nullptr);
    ~CreateWindow();
};

#endif // CREATEWINDOW_H
