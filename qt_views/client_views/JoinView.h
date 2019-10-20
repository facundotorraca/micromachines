#ifndef JOINVIEW_H
#define JOINVIEW_H

#include <QDialog>
#include <../qt_views/ui_joinView.h>
#include <common/ProtocolSocket.h>

class JoinView : public QDialog {
  Q_OBJECT
  Ui::JoinView ui;
  ProtocolSocket &ps;
  QStringList matches;
public:
  explicit JoinView(ProtocolSocket &ps, std::string matches, QWidget *parent = nullptr);
  ~JoinView();
 private slots:
  void on_btnBoxJoin_accepted();
};

#endif // JOINVIEW_H
