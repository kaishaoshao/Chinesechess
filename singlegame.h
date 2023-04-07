#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "board.h"

class SingleGame:public Board
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = 0);
    ~SingleGame();
    //纯虚函数与抽象类，纯虚函数没有函数体，只有函数名，因此不能被调用，徒有其名，而无其实留在派生类中带定义，只有派生类定义后才能使用
    virtual void click(int id, int row, int col);
    Step* getbestMove();
    //所有可能走棋 采用数组保存
    void getAllstep(QVector<Step*>& steps);

    void fackMove(Step *step);
    void unfackMove(Step *step);
    //判断分数
    int setScore();
    //取最小值
    int getMinScore(int endNum,int cutlast);
    int getMaxScore(int endNum,int cutlast);

    int  endNum;     //考虑的层次

public slots:
    void computerMove();

private:


};

#endif // SINGLEGAME_H
