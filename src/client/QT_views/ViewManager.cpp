//
// Created by Alejo Acevedo on 18/10/2019.
//

#include "ViewManager.h"
#include "./views/menuwindow.h"
#include "./views/connectview.cpp"
#include <iostream>
#include <QtCore/QFile>
#include <QtMultimedia/QMediaPlayer>
#include <QtCore/QFileInfo>
#include <QFontDatabase>


ViewManager::ViewManager(int argc, char *argv[])
                        : mainApp(argc, argv),
                        sck(),
                        arranged(false),
                        box_check(false) {
    QFontDatabase::addApplicationFont(QFileInfo("assets/fonts/Kenney Pixel.ttf").absoluteFilePath());
    QFile styleFile(STYLESHEET_PATH);
    styleFile.open(QFile::ReadOnly);
    QString StyleSheet = styleFile.readAll();
    this->mainApp.setStyleSheet(StyleSheet);
    this->set_playlist();
}

void ViewManager::set_playlist() {
    this->playlist.addMedia(QUrl::fromLocalFile(QFileInfo(MUSIC_PATH).absoluteFilePath()));
    this->playlist.setPlaybackMode(QMediaPlaylist::Loop);
    this->player.setPlaylist(&this->playlist);
}

ProtocolSocket ViewManager::run() {
    ConnectView connectView(this->sck);
    connectView.show();
    this->mainApp.exec();
    ProtocolSocket ps(std::move(this->sck));
    if (!ps.is_connected()) {
        return std::move(ps);
    }
    this->player.play();
    MenuWindow menuWindow(ps);
    menuWindow.show();
    this->mainApp.exec();
    this->player.stop();
    if (!menuWindow.is_game_arranged()){
        return std::move(ps);
    }
    this->box_check = menuWindow.get_bot_check();
    this->arranged = true;
    return std::move(ps);
}

bool ViewManager::is_game_arranged() {
    return this->arranged;
}

bool ViewManager::use_bot() {
    return this->box_check;
}