#include "gamenet.h"
#include <QDebug>
GameNet::GameNet(bool isserver)
{
     server = nullptr;
     socket = nullptr;
     if(isserver)
     {
         server = new QTcpServer(this);
         server->listen(QHostAddress::Any,9999);
         connect(server,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));

     }
     else
     {
         socket = new QTcpSocket(this);
         socket->connectToHost(QHostAddress("127.0.0.1"),9999);

     }
}

void GameNet::slotNewConnection()
{
    qDebug()<<"sdsdf";
    if(socket)
    {
        return;
    }
    socket = server->nextPendingConnection();

}
