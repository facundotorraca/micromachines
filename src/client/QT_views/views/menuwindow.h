#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <common/Socket.h>
#include <client/QT_views/ui_menuwindow.h>
#include <common/ProtocolSocket.h>
#include <QtCore/QThread>
#include <client/QT_views/Waiter.h>

#define ERROR_CONN_MSG "PROBLEMA DE CONEXION CON EL SERVIDOR"

#define MAIN_PAGE 0
#define CREATE_PAGE 1
#define JOIN_PAGE 2
#define START_PAGE 3
#define WAIT_PAGE 4
#define ERROR_SERVER_PAGE 5

#define START_MATCH 0
#define CANCEL_MATCH 1

#define JOIN_COMMAND 1
#define CREATE_COMMAND 2

#define GOOD_FLAG 0
#define BAD_FLAG 1

#define CLOSE_CONNECTION 3

class MenuWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MenuWindow(ProtocolSocket &ps, QWidget *parent = nullptr);
    bool is_game_arranged();
    bool get_bot_check();
    ~MenuWindow();

private slots:
    void on_createBtn_clicked();
    void on_joinBtn_clicked();
    void on_quitBtn_clicked();
    void on_matchList_itemSelectionChanged();
    void on_updateBtn_clicked();
    void on_joinBtnBox_accepted();
    void on_joinBtnBox_rejected();
    void on_createBtnBox_accepted();
    void on_createBtnBox_rejected();
    void on_startBtn_clicked();

public slots:
    void handle_wait(int result);

private:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    bool set_user_name(std::string user_name);
    bool set_match_name(std::string match_name);
    void update_matches();
    void update_maps();

    Ui::MenuWindow ui;
    ProtocolSocket &ps;
    bool arranged;
    QThread wait_thread;
    Waiter waiter_worker;
    uint8_t map_selected;

};

#endif // MENUWINDOW_H
