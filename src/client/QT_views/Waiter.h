//
// Created by alejoacevedo on 11/22/19.
//

#ifndef MICROMACHINES_WAITER_H
#define MICROMACHINES_WAITER_H

#include <common/ProtocolSocket.h>
#include <iostream>
#include <QtCore/QObject>

class Waiter : public QObject {
    Q_OBJECT

    ProtocolSocket &ps;

public:
    Waiter(ProtocolSocket &ps);

public slots:
    void wait_response();

signals:
    void resultReady(int result);
};


#endif //MICROMACHINES_WAITER_H
