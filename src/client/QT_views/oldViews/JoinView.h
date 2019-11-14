#ifndef JOINVIEW_H
#define JOINVIEW_H

#include <QDialog>
#include <common/ProtocolSocket.h>
#include <client/QT_views/ui_joinView.h>

class JoinView : public QDialog {
    Q_OBJECT
    Ui::JoinView ui;
    ProtocolSocket &ps;
    QStringList matches;
    bool joined;
public:
    explicit JoinView(ProtocolSocket &ps, std::string matches, QWidget *parent = nullptr);
    bool is_joined();
    ~JoinView();
 private slots:
    void on_btnBoxJoin_accepted();
    void on_matchList_itemSelectionChanged();
};

#endif // JOINVIEW_H
