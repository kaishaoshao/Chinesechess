#ifndef GAMENET_H
#define GAMENET_H
#include "board.h"
#include <QTcpServer>
#include <QTcpSocket>


class GameNet : public Board
{
public:
    GameNet(bool isserver);

    QTcpServer* server;
    QTcpSocket* socket;

public slots:
    void slotNewConnection();

};

#endif // GAMENET_H
