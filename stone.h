#ifndef STONE_H
#define STONE_H

#include <QString>

class stone
{
public:
    stone();

    enum TYPE{Car,Gun,Horse,Premier,Elephant,Soldier,Mandarins,Arms,Pawns,King,Generals};
    int row;        //横坐标
    int col;        //纵坐标
    int id;         //编号
    bool isdead;      //是否死亡
    bool isblack;     //颜色
    TYPE type;      //种类

    //初始化棋子
    void init(int ID);
    //设置边界
    void rotate();

    //判断棋子的种类
    QString getclass();


};

#endif // STONE_H
