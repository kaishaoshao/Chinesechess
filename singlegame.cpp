#include "singlegame.h"
#include <QTimer>
#include <QDebug>

SingleGame::SingleGame(QWidget *parent) : Board(parent)
{
   endNum = 4;
}

SingleGame::~SingleGame()
{

}
void SingleGame::click(int id, int row, int col)
{
    //非红棋走，无反应
    if(!this->isTurnRed)
     {
        return;
}
    Board::click(id,row,col);
    //当是黑棋走
    if(!this->isTurnRed)
    {
        //定时器
        QTimer::singleShot(10,this,SLOT(computerMove()));
    }


}

Step *SingleGame::getbestMove()
{
    //1.看看有哪些步骤可以走
    QVector<Step*> steps;
    getAllstep(steps);
     //2.试着走一下
     //3.评估走的结果
     //最高分
     int maxScore = -300000 ;
     Step* ret = nullptr;
     while (steps.count())
     {
         Step* step = steps.last();
         steps.removeLast();
         //将棋子移动后返回
         fackMove(step);
         int score = getMinScore(endNum-1,maxScore);
         unfackMove(step);
         if(score > maxScore)
         {
             maxScore = score;
             ret = step;
         }
         else
         {
             delete step;
         }
     }
     //4.取最好结果作为参考
    return ret;
}
//电脑走棋
void SingleGame::computerMove()
{
    Step* step = getbestMove();
    moveStone(step->_moveid,step->_killid,step->_rowTo,step->_colTo);
    delete step;
    update();
}

void SingleGame::getAllstep(QVector<Step*>& steps)
{
    //遍历所有棋子
    int min,max;
    if(!this->isTurnRed)
    {
        min = 0;
        max = 16;
    }
    else
    {
        min = 16;
        max = 32;
    }
    for(int i = min; i < max; i++)
    {
        if(this->s[i].isdead) continue;
        for (int row = 0; row <= 9; row++)
        {
            for (int col = 0;col <= 8; col++)
            {
                //先判断目标点，是否含有棋子
                int killid = this->getStonID(row,col);
                if(sameColor(killid,i))  //判断棋子颜色是否相同
                    continue;
                if(canMove(i,row,col,killid))
                {
                    saveStep(i,killid,row,col,steps);
                }
            }
        }
    }
}

void SingleGame::fackMove(Step *step)
{
    killStone(step->_killid);
    moveStone(step->_moveid, step->_rowTo, step->_colTo);
}

void SingleGame::unfackMove(Step *step)
{
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}
//计算评价分数的  依据将每种棋子设置一种分数来判断
int SingleGame::setScore()
{
    int redTotalScore = 0;
    int blackTotalScore = 0;
    static int ChessScore[] = { 1000,600,500,300,300,300,300,200,200,15000,15000};

    //黑棋分 - 红棋分
    for(int i = 0;i<16;i++)
    {
        if(s[i].isdead) continue;
        redTotalScore +=  ChessScore[s[i].type];
    }
    for(int i = 16;i<32;i++)
    {
        if(s[i].isdead) continue;
        blackTotalScore +=  ChessScore[s[i].type];
    }
    return  redTotalScore-blackTotalScore;

}
 //象棋行动两步的基础
int SingleGame::getMinScore(int endNum,int cutlast)
{
    if(endNum == 0)
    {
        return setScore();
    }
    QVector<Step*> steps;
    getAllstep(steps);         //红棋的步骤
    int minScore = 100000;
    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();
        //将棋子移动后返回
        fackMove(step);
        int score = getMaxScore(endNum-1,minScore);
        unfackMove(step);
        delete step;
        if(score <= cutlast)
        {
            while (steps.count())
            {
                Step* step = steps.last();
                steps.removeLast();
                delete step;
            }
            return score;
        }

        if(score < minScore)
        {
          minScore =  score;
        }

    }
    return minScore;
}

int SingleGame::getMaxScore(int endNum,int cutlast)
{
    if(endNum == 0)
    {
        return setScore();
    }
    QVector<Step*> steps;
    getAllstep(steps);

    int maxScore = -100000;
    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();
        //将棋子移动后返回
        fackMove(step);
        int score = getMinScore(endNum-1,maxScore);
        unfackMove(step);
        delete step;
        if(score >= cutlast)
        {
            while (steps.count())
            {
                Step* step = steps.last();
                steps.removeLast();
                delete step;
            }
            return score;
        }
        if(score > maxScore)
        {
          maxScore =  score;
        }


    }
    return maxScore;
}




