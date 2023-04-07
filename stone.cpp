#include "stone.h"
#include "board.h"

stone::stone()
{

}
//初始化棋子
void stone::init(int ID)
{
   struct
   {
       int row, col;
       stone::TYPE type;
   }

   chess[32]=
   {
   //黑棋
   {0,0,stone::Car},
   {0,1,stone::Horse},
   {0,2,stone::Elephant},
   {0,3,stone::Mandarins},
   {0,4,stone::Generals},
   {0,5,stone::Mandarins},
   {0,6,stone::Elephant},
   {0,7,stone::Horse},
   {0,8,stone::Car},

   {2,1,stone::Gun},
   {2,7,stone::Gun},
   {3,0,stone::Pawns},
   {3,2,stone::Pawns},
   {3,4,stone::Pawns},
   {3,6,stone::Pawns},
   {3,8,stone::Pawns},

   //红棋

   {9,0,stone::Car},
   {9,1,stone::Horse},
   {9,2,stone::Premier},
   {9,3,stone::Soldier},
   {9,4,stone::King},
   {9,5,stone::Soldier},
   {9,6,stone::Premier},
   {9,7,stone::Horse},
   {9,8,stone::Car},

   {7,1,stone::Gun},
   {7,7,stone::Gun},
   {6,0,stone::Arms},
   {6,2,stone::Arms},
   {6,4,stone::Arms},
   {6,6,stone::Arms},
   {6,8,stone::Arms},
   };
    this->id = ID;
    this->isdead = false;
    if(ID<16)
    {
        this->isblack = true;
    }

    else  this->isblack = false;

    if(ID<16)
    {
         this->row =  chess[ID].row;
         this->col =  chess[ID].col;
         this->type = chess[ID].type;
    }
    else{
        this->row = chess[ID].row;
        this->col = chess[ID].col;
        this->type = chess[ID].type;
    }
}

void stone::rotate()
{
    this->col = col;
    this->row = row;
}

//判断棋子的种类
QString stone::getclass()
{
    switch (this->type)
    {
        case Car: return "車";
        case Gun: return "炮";
        case Horse: return "马";
        case Premier: return "相";
        case Elephant: return "象";
        case Soldier: return "仕";
        case Mandarins: return "士";
        case Arms: return "兵";
        case Pawns: return "卒";
        case King: return "帥";
        case Generals: return "将";
    }

    return "ERROR";
}
