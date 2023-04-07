#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QVector>
#include "stone.h"
#include "step.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Board; }
QT_END_NAMESPACE

class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    ~Board();

    QPoint origin; //棋盘初始点坐标
    int d;//格子边长
    stone s[32];//棋子
    int r;    //棋子半径
    int isSelect;   //记录棋子,是否选中
    //交换走棋
    bool isTurnRed;

public:
    //初始化
    void initBoard(bool bredSide);
    //返回象棋棋盘行列对应的坐标
    QPoint Center(int row,int col);
    QPoint Center(int id);
    //绘制棋子   
    void DrawStone(QPainter &painter,int id);
    //棋盘绘制(绘图事件)
    void paintEvent(QPaintEvent *);
    //绘制兵炮停靠点
    void drawAngle(QPainter &p,QPoint point);
    //走棋(鼠标点击事件)
    void mouseReleaseEvent(QMouseEvent *ev);
    //获得棋盘的行列,是否在棋盘内
    bool getRowCol(QPoint pt,int &row,int &col);
    //判断是否能够走棋
    bool canMove(int moveid,int row,int col,int killid);
    //判断是否能够选择棋子
    bool canSelect(int id);
    //象棋走棋
    bool canMoveCar(int moveid,int row,int col);
    bool canMoveGun(int moveid,int row,int col);
    bool canMoveHorse(int moveid,int row,int col);
    bool canMoveElephant(int moveid,int row,int col);
    bool canMoveMandarins(int moveid,int row,int col);
    bool canMoveGenerals(int moveid,int row,int col);
    bool canMovePawns(int moveid,int row,int col);
    //勾股定理计算棋子应该移动范围
    int Gougu(int moveid,int row,int col);
    //判断某行某位置有没有棋子
    int Havestone(int row,int col);
    //统计直线上棋子个数
    int CountnumLine(int row, int col ,int Row,int Col);
    //判断颜色
    bool isred(int id);
    bool isDead(int id);
    //获取棋子id
    int getStonID(int row, int col);

public:

    //人工智能走棋
    void click(QPoint pt);
    virtual void click(int id,int row,int col);

    //尝试选择棋子
    void trySelectStone(int id);
    //尝试移动
    void tryMoveStone(int killid,int row,int col);
    //判断颜色
    bool sameColor(int id_first,int id_second);
    //移动棋子
    void moveStone(int moveid,int killid,int row,int col);
    void moveStone(int moveid,int row,int col);
    //保存步骤
    void saveStep(int moveid,int killid,int row,int col,QVector<Step*>& step);
    //是否死亡
    void reliveStone(int id);
    void killStone(int id);
    bool isBottomSide(int id);

    void back(Step* step);
    virtual void back();

    void back_first();
    void slotBack();

public:
   QVector <Step*> steps;   //保留步骤
   bool bSide;

private:
    Ui::Board *ui;
};
#endif // BOARD_H
