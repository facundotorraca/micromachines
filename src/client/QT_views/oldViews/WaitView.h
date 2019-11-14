#ifndef WAITWINDOW_H
#define WAITWINDOW_H

#include <QDialog>
#include <common/ProtocolSocket.h>
#include <client/QT_views/ui_waitView.h>

class WaitView : public QDialog
{
    Q_OBJECT

public:
    explicit WaitView(ProtocolSocket &ps, QWidget *parent = nullptr);
    void show();
    virtual ~WaitView();

private:
    ProtocolSocket &ps;
    Ui::WaitWindow ui;

private slots:
    void on_waitBtn_clicked();


};

#endif // WAITWINDOW_H
