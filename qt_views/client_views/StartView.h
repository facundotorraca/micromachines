#ifndef STARTVIEW_H
#define STARTVIEW_H

#include <QDialog>
#include <ui_startView.h>
#include <common/ProtocolSocket.h>

class StartView : public QDialog {
    Q_OBJECT

public:
    explicit StartView(ProtocolSocket &ps, QWidget *parent = nullptr);
    virtual ~StartView();

private:
    Ui::StartView ui;
    ProtocolSocket &ps;

 private slots:
    void on_startBtn_clicked();

};

#endif // STARTVIEW_H
