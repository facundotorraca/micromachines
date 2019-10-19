#ifndef JOINVIEW_H
#define JOINVIEW_H

#include <QDialog>
#include <client/qt_views/ui_joinView.h>
#include <common/ProtocolSocket.h>

class JoinView : public QDialog {
  Q_OBJECT
  Ui::JoinView ui;
  ProtocolSocket &ps;
  std::vector<std::string> matches;
public:
  explicit JoinView(ProtocolSocket &ps, std::string matches, QWidget *parent = nullptr);
  ~JoinView();
};

#endif // JOINVIEW_H
