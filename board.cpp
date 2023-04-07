#include "board.h"
#include "ui_board.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#define GetRowCol(row_f, col_f,id) \
    int row_f = s[id].row;\
    int col_f = s[id].col

Board::Board(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Board)
{
    this->d = 80;
    this->r = 40;
    setMinimumSize(r*18+1,r*20+1);
    initBoard(true);
    ui->setupUi(this);
}
Board::~Board()
{
    delete ui;
}

void Board::initBoard(bool bredSide)
{
    origin = QPoint(60,60);
    for (int i=0;i<32;i++)
    {
        s[i].init(i);
    }
    if(bredSide)
    {
        for (int i =0;i<32;i++)
        {
            s[i].rotate();
        }
    }

    isSelect = -1;
    isTurnRed = true;
    bSide = !bredSide;
    update();
}
//将坐标轴转换为像素坐标点
QPoint Board::Center(int row, int col)
{
    return QPoint(origin.x()+d*col,origin.y()+d*row);
}

QPoint Board::Center(int id)
{
    return Center(s[id].row,s[id].col);
}
//绘制棋子
void Board::DrawStone(QPainter &painter, int id)
{
  QPen pen;
  pen.setWidth(1);
  painter.setPen(pen);
  //求中心点
  QPoint c = Center(id);
  //构造图像
  QRect rect = QRect(c.rx()-r,c.ry()-r,r*2,r*2);
  //棋子不存在
  if(s[id].isdead)
      return;
  //如果棋子被选中
  if(id == isSelect)
     painter.setBrush(QBrush(Qt::gray));
  else
     painter.setBrush(QBrush(QColor(234,173,26)));

   //绘制椭圆函数DrawEllipse
  painter.drawEllipse(Center(s[id].row,s[id].col),r, r);
  painter.drawEllipse(Center(s[id].row,s[id].col),r-3, r-3);
  //绘制棋子颜色
  if(s[id].isblack)
  {
       painter.setPen(Qt::black);

  }
   else  painter.setPen(Qt::red);

  //写字,参数说明draw(对象,字,对齐方式）
  painter.setFont(QFont("楷体",r,700));
  painter.drawText(rect,s[id].getclass(),QTextOption(Qt::AlignCenter));


}
//创建棋盘雏形，利用坐标点原理
void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //设置画笔
    QPen pen;
    pen.setWidth(3);
    painter.setPen(pen);
    //绘制棋盘外围边框
    painter.drawRect(QRect(origin.x()-4,origin.y()-4,d*8+10,d*9+10));
    //绘制棋盘内线
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawRect(QRect(origin,Center(9,8)));
    //绘制8横7竖
    for (int i=1;i<=8;i++)
    {
        //drawline函数就是两点之间画直线，电脑左上角为坐标轴起点，QPoint(d,d)点坐标
        painter.drawLine(Center(i,0),Center(i,8));
        if(i<8)
        {
            painter.drawLine(Center(0,i),Center(4,i));
            painter.drawLine(Center(5,i),Center(9,i));
        }
    }
     //九宫格
    painter.drawLine(Center(0,3),Center(2,5));
    painter.drawLine(Center(2,3),Center(0,5));
    painter.drawLine(Center(7,3),Center(9,5));
    painter.drawLine(Center(9,3),Center(7,5));

    //绘制楚河汉界
    QPainterPath s;
    painter.setPen(Qt::gray);
    painter.setFont(QFont("楷体",35,r));
    painter.drawText(QRect(Center(4,1),Center(5,3)),"楚河",QTextOption(Qt::AlignCenter));
    painter.drawText(QRect(Center(4,5),Center(5,7)),"漢界",QTextOption(Qt::AlignCenter));

    //绘制棋子炮的停靠点
    drawAngle(painter,Center(2,1));
    drawAngle(painter,Center(2,7));
    drawAngle(painter,Center(7,1));
    drawAngle(painter,Center(7,7));
    //中间6个兵停靠点
    drawAngle(painter,Center(3,2));
    drawAngle(painter,Center(3,4));
    drawAngle(painter,Center(3,6));
    drawAngle(painter,Center(6,2));
    drawAngle(painter,Center(6,4));
    drawAngle(painter,Center(6,6));

    drawAngle(painter,Center(3,0));
    drawAngle(painter,Center(3,8));
    drawAngle(painter,Center(6,0));
    drawAngle(painter,Center(6,8));

   //绘制32个棋子
   for (int i=0;i<32;i++)
   {
       DrawStone(painter,i);
       }
}

void Board::drawAngle(QPainter &p, QPoint point)
{
    QPen pen;
    pen.setWidth(2);
    p.setPen(pen);
    int X = point.x();
    int Y = point.y();
    float R = d/9.5;
    if(point.x() == 60)
     {

        p.drawLine(X+R,Y-R,X+2*R,Y-R);
        p.drawLine(X+R,Y+R,X+2*R,Y+R);
        p.drawLine(X+R,Y-2*R,X+R,Y-R);
        p.drawLine(X+R,Y+R,X+R,Y+2*R);

    }
    else if(point.x() == 700)
    {
        p.drawLine(X-2*R,Y-R,X-R,Y-R);
        p.drawLine(X-2*R,Y+R,X-R,Y+R);
        p.drawLine(X-R,Y-2*R,X-R,Y-R);
        p.drawLine(X-R,Y+R,X-R,Y+2*R);
    }

    else
    {
        p.drawLine(X-2*R,Y-R,X-R,Y-R);
        p.drawLine(X-2*R,Y+R,X-R,Y+R);
        p.drawLine(X+R,Y-R,X+2*R,Y-R);
        p.drawLine(X+R,Y+R,X+2*R,Y+R);

        p.drawLine(X-R,Y-2*R,X-R,Y-R);
        p.drawLine(X-R,Y+R,X-R,Y+2*R);
        p.drawLine(X+R,Y-2*R,X+R,Y-R);
        p.drawLine(X+R,Y+R,X+R,Y+2*R);
    }

}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() != Qt::LeftButton)
    {
        return ;
    }
    click(ev->pos());

// QPoint pt = ev->pos();
//   //将pt转换成象棋的行列值
//   //判断行列值上面有没有棋子
//   int row,col;
//   bool bret = getRowCol(pt,row,col);
//   if(bret == false) return; //点在棋盘外
//   int i;
//   int clickid = -1;
//   for(i=0;i<32;++i)
//   {
//       if(s[i].row == row && s[i].col == col && s[i].isdead == false)
//       {
//           break;
//       }
//   }
//   if(i<32)
//   {
//       clickid = i;

//   }
//   //
//   if(isSelect == -1)
//   {
//      if(clickid != -1)
//      {
//          if(isTurnRed == !s[clickid].isblack)
//          isSelect = clickid;
//          update();
//      }
//   }
//   else
//   {
//       //走棋
//       if(canMove(isSelect,row,col,clickid))
//       {
//           s[isSelect].row = row;
//           s[isSelect].col =col;
//           if(clickid != -1)
//           {
//               s[clickid].isdead = true;
//           }
//           isSelect = -1;
//           isTurnRed = !isTurnRed;
//           update();
//       }

//   }

}

bool Board::getRowCol(QPoint pt, int &row, int &col)
{
    for (row = 0;row<=9;row++)
    {
        for (col = 0;col<=8;col++)
        {
            QPoint c=Center(row,col);
            //勾股定理 //效率不高
            int dx = c.x() - pt.x();
            int dy = c.y() - pt.y();
            int dist = dx*dx+dy*dy;
            if(dist < r*r)
                return true;
        }
    }
    return false;
}

bool Board::canMove(int moveid, int row, int col, int killid)
{
    if((s[moveid].isblack == s[killid].isblack)&&killid != -1)
    {

        isSelect = killid;
        update();
        return false;
    }

    switch(s[moveid].type)
    {
        case stone::Car: return canMoveCar(moveid, row,  col); break;
        case stone::Gun: return canMoveGun(moveid, row,  col);break;
        case stone::Horse: return canMoveHorse(moveid, row,  col); break;
        case stone::Elephant: return canMoveElephant(moveid, row,  col);break;
        case stone::Premier: return canMoveElephant(moveid, row,  col);break;
        case stone::Mandarins: return canMoveMandarins(moveid, row,  col);break;
        case stone::Soldier: return canMoveMandarins(moveid, row,  col);break;
        case stone::Generals: return canMoveGenerals(moveid, row,  col);break;
        case stone::King:return canMoveGenerals(moveid, row,  col);break;
        case stone::Pawns: return canMovePawns(moveid, row,  col); break;
        case stone::Arms: return canMovePawns(moveid, row,  col);break;
    }

    return true;
}
//选择棋子
bool Board::canSelect(int id)
{
    return isTurnRed == !(s[id].isblack);
}
//車直行
bool Board::canMoveCar(int moveid, int row, int col)
{
    if(CountnumLine(row,col,s[moveid].row,s[moveid].col) == 0)
     {
        return true;
    }
    return false;
}
//隔山打牛炮
bool Board::canMoveGun(int moveid, int row, int col)
{
    //移动
  if(Havestone(row,col) == -1 && CountnumLine(row,col,s[moveid].row,s[moveid].col)==0)
  {
      return true;
  }
  //隔山打牛吃子
  if(Havestone(row,col) != -1 && CountnumLine(row,col,s[moveid].row,s[moveid].col)==1)
  {
       return true;
  }
  return false;
}
//马走日
bool Board::canMoveHorse(int moveid, int row, int col)
{
    //勾股定理 
    int dis = Gougu(moveid, row, col);
    if(dis == 12 && Havestone(s[moveid].row,(col+s[moveid].col)>>1)==-1) //没有拐脚
    {
        return true;
    }
    else if(dis == 21 && Havestone((row+s[moveid].row)>>1,s[moveid].col)==-1)
    {
        return true;
    }
    return false;
}
 //士的移动范围在九宫格内,移动的步长是斜线
bool Board::canMoveMandarins(int moveid, int row, int col)
{

    //黑棋 士
    if(s[moveid].isblack)
    {
        if(row > 2)
            return false;
    }
    //红棋 士
    else
    {
       if(row < 7)
          return false;
    }

    if(col < 3)
        return false;
    if(col >5)
        return false;
    //勾股定理
    int dis = Gougu(moveid, row, col);
    if(dis == 11)
    {
        return true;
    }
    return false;
}
 //相或者象的移动范围楚河汉界的一边不能越界，象飞田
bool Board::canMoveElephant(int moveid, int row, int col)
{
    //黑棋 象
    if(s[moveid].isblack)
    {
        if(row > 4)
            return false;
    }
    //红棋 相
    else
    {
       if(row < 5)
          return false;

    }
    //勾股定理
    int dis = Gougu(moveid, row, col);
    if(dis == 22 && Havestone((row+s[moveid].row)>>1,(col+s[moveid].col)>>1) == -1)
    {
        return true;
    }
    return false;
}
 //将军的移动范围在九宫格内,移动的步长是一个格子
bool Board::canMoveGenerals(int moveid, int row, int col)
{

    //黑棋 将
    if(s[moveid].isblack)
    {
        if(row > 2)
            return false;
    }
    //红棋 帅
    else
    {
       if(row < 7)
          return false;
    }
    if(col < 3)
        return false;
    if(col >5)
        return false;
    //勾股定理
    int dis = Gougu(moveid, row, col);
    if(dis == 1 || dis ==10)
    {
        return true;
    }
    return false;
}
 //小兵的移动是一直向前,移动的步长是一个格子
bool Board::canMovePawns(int moveid, int row, int col)
{

    //黑棋 卒
    if(s[moveid].isblack)
    {
        if(s[moveid].row>row)
            return false;
    }
    //红棋 兵
    else
    {
       if(s[moveid].row<row)
          return false;
    }
    //勾股定理
    int dis = Gougu(moveid, row, col);
    if(dis ==10)
    {
        return true;
    }
    else if(dis == 1&&s[moveid].isblack&&s[moveid].row>4)
    {
        return true;
    }
    else if(dis == 1&&!s[moveid].isblack&&s[moveid].row<5)
    {
         return true;
    }

    return false;
}

 //勾股定理计算棋子应该移动范围
int Board::Gougu(int moveid, int row, int col)
{
    int Row = s[moveid].row-row;
    int Col = s[moveid].col-col;
    //勾股定理
    return abs(Row)*10+abs(Col);
}

//判断某行某位置有没有棋子
int Board::Havestone(int row, int col)
{
    for (int i =0;i < 32;i++)
    {

        if((row == s[i].row && col ==s[i].col)&&!s[i].isdead)
        {
           return i;
        }
    }
    return -1;
}

//统计直线上棋子个数
int Board::CountnumLine(int row, int col, int Row, int Col)
{
    int max,min,count=0;
    if(row != Row && col !=Col)
    {
        return -1;
    }
    if(row == Row)
    {
        if(col < Col)
        {
            max = Col;
            min = col;
        }
        else
        {
            max = col;
            min = Col;
        }
        for (int i = min+1;i < max;i++)
        {
            if(Havestone(row,i)>=0)
            {
                count++;
            }          
        }
    }

    else if (col == Col)
    {
       if(row < Row)
       {
           max = Row;
           min = row;
       }
       else
       {
           max = row;
           min = Row;
       }
       for (int i = min+1;i < max;i++)
       {
           if(Havestone(i,col)>=0)
           {
               count++;
           }
        }
    }
    return count;
}

//判断颜色
bool Board::isred(int id)
{
    return !(s[id].isblack);
}

bool Board::isDead(int id)
{
    if(id == -1) return true;
    return s[id].isdead;
}

//点击坐标点
void Board::click(QPoint pt)
{

    int row,col;
    bool isClicked = getRowCol(pt,row,col);
    if(!isClicked)
    {
        return ;
    }
    int id = getStonID(row,col);

    click(id,row,col);

}

//点击
void Board::click(int id, int row, int col)
{
    qDebug()<<"click"<<this->isSelect;
    if(this->isSelect == -1)
    {
        trySelectStone(id);
    }
    else
    {
       tryMoveStone(id,row, col);
    }
}

void Board::trySelectStone(int id)
{
    if(id == -1)
    {
        return ;
    }

    if(!canSelect(id))
    {
        return ;
    }
    isSelect = id;
    update();
}

void Board::tryMoveStone(int killid, int row, int col)
{
    if(killid != -1 && sameColor(killid,isSelect))
     {
        trySelectStone(killid);
        return;
     }
    bool ret = canMove(isSelect,row,col,killid);
    if(ret)
    {
        moveStone(isSelect,killid,row,col);
        isSelect = -1;
        update();
    }


}

//吃子时
bool Board::sameColor(int id_first, int id_second)
{
    if(id_first == -1 || id_second == -1)
        return false;
    return isred(id_first) == isred(id_second);
}

void Board::moveStone(int moveid, int killid, int row, int col)
{
    saveStep(moveid,killid,row,col,steps);
    killStone(killid);
    moveStone(moveid,row,col);
}

void Board::moveStone(int moveid, int row, int col)
{
   s[moveid].row = row;
   s[moveid].col = col;
   isTurnRed = !isTurnRed;
}

void Board::saveStep(int moveid, int killid, int row, int col, QVector<Step*>& step)
{
    GetRowCol(row_f,col_f,moveid);
    Step* steps = new Step;
    steps->_colFrom = col_f;
    steps->_rowFrom = row_f;
    steps->_colTo = col;
    steps->_rowTo = row;
    steps->_killid = killid;
    steps->_moveid = moveid;

    step.append(steps);

}

//棋子是否死亡
void Board::reliveStone(int id)
{
    if(id == -1) return;
    s[id].isdead = false;

}

void Board::killStone(int id)
{
    if(id == -1) return;
    s[id].isdead = true;
}
//判断棋子种类
bool Board::isBottomSide(int id)
{
    return bSide == !(s[id].isblack);
}

void Board::back(Step *step)
{
    reliveStone(step->_killid);
    moveStone(step->_moveid,step->_rowFrom,step->_colFrom);
}

void Board::back()
{
   back_first();
}

void Board::back_first()
{
    if(this->steps.size() == 0)
        return ;
    Step* step =this->steps.last();
    steps.removeLast();
    back(step);

    update();
    delete step;
}

void Board::slotBack()
{
  back();
}

//获得棋子id
int Board::getStonID(int row, int col)
{
    for(int i=0;i<32;i++)
    {
        if(s[i].row==row && s[i].col == col && !isDead(i))
        {
            return i;
        }

     }
   return -1;

}



