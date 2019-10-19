#ifndef CONECTVIEW_H
#define CONECTVIEW_H

#include <QDialog>
#include <QDialogButtonBox>
#include <common/Socket.h>
#include <client/qt_views/client_views/ConectView.h>

class ConectView : public QDialog {
 Q_OBJECT
  Ui::ConectView ui;
  Socket &socket;
 public:
  explicit ConectView(Socket &sck, QWidget *parent = nullptr);
  virtual ~ConectView();
 private slots:
  void on_btnBox_accepted();
};

#endif // CONECTVIEW_H
