#ifndef CONECTVIEW_H
#define CONECTVIEW_H

#include <common/Socket.h>
#include <common/ProtocolSocket.h>
#include <QtWidgets/QDialog>
#include <client/QT_views/ui_connectview.h>


class ConnectView : public QDialog {
    Q_OBJECT

 public:
    explicit ConnectView(Socket &sck, QWidget *parent = nullptr);
    virtual ~ConnectView();

 private slots:
    void on_connectionBtnBox_accepted();
    void on_connectionBtnBox_rejected();

 private:
    Ui::ConnectView ui;
    Socket &socket;
};

#endif // CONECTVIEW_H
