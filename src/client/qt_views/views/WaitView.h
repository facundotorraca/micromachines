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
    virtual ~WaitView();

private:
    ProtocolSocket &ps;
    Ui::WaitWindow ui;

private slots:
    void on_waitBtn_clicked();
};

#endif // WAITWINDOW_H
