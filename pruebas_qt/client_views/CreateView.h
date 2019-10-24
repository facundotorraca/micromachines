#ifndef CREATEVIEW_H
#define CREATEVIEW_H

#include <QDialog>
#include <../QT_views/ui_createView.h>
#include <common/ProtocolSocket.h>

class CreateView : public QDialog {
    Q_OBJECT
    ProtocolSocket &ps;
    bool created;
 public:
    explicit CreateView(ProtocolSocket &ps, QWidget *parent = nullptr);
    bool is_created();
    virtual ~CreateView();
 private:
    Ui::CreateView ui;

 private slots:
    void on_btnBoxCreate_accepted();
};

#endif // CREATEVIEW_H
