#include "board.h"
#include "singlegame.h"
#include <QApplication>
#include <gamenet.h>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(NULL,"server or client","作为服务器");

    bool bServer = false;
    if(ret == QMessageBox::Yes)
    {
        bServer = true;
    }
    GameNet board(bServer);
    board.setWindowTitle("中国象棋");
    board.show();
    return a.exec();
}

