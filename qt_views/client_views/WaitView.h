#ifndef WAITWINDOW_H
#define WAITWINDOW_H

#include <QDialog>
#include <ui_waitView.h>
#include <common/ProtocolSocket.h>

class WaitView : public QDialog
{
    Q_OBJECT

public:
    explicit WaitView(ProtocolSocket &ps, QWidget *parent = nullptr);
    void wait_start();
    virtual ~WaitView();

private:
    ProtocolSocket &ps;
    Ui::WaitWindow ui;
};

#endif // WAITWINDOW_H
