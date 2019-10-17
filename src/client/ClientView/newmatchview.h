#ifndef NEWMATCHVIEW_H
#define NEWMATCHVIEW_H

#include <QMainWindow>

namespace Ui {
class NewMatchView;
}

class NewMatchView : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMatchView(QWidget *parent = nullptr);
    ~NewMatchView();

private:
    Ui::NewMatchView *ui;
};

#endif // NEWMATCHVIEW_H
