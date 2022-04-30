#include <iostream>
#include <stdlib.h>
#include "../Stack.h"
using namespace std;

typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status; //迷宫单元状态
//原始可用的、在当前路径上的、所有方向均尝试失败后回溯过的、不可使用的（墙）
typedef enum { UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY } ESWN; //单元的相对邻接方向
//未定、东、南、西、北、无路可通
#define LABY_MAX 24 //最大迷宫尺寸
inline ESWN nextESWN ( ESWN eswn ) { return ESWN ( eswn + 1 ); } //依次转至下一邻接方向
int labySize;

struct Cell { //迷宫格点
   int x, y; Status status; //x坐标、y坐标、类型
   ESWN incoming, outgoing; //进入、走出方向
};


Cell laby[LABY_MAX][LABY_MAX]; //迷宫
Cell* startCell;
Cell* goalCell;

void randLaby() { //生成随机的迷宫
   labySize = LABY_MAX / 2 + rand() % ( LABY_MAX / 2 );
   for ( int i = 0; i < labySize; i++ )
      for ( int j = 0; j < labySize; j++ ) {
         laby[i][j].x = i;
         laby[i][j].y = j;
         laby[i][j].incoming   =
            laby[i][j].outgoing   =   UNKNOWN;
         laby[i][j].status = WALL; //边界格点必须是墙
      }
   for ( int i = 1; i < labySize - 1; i++ )
      for ( int j = 1; j < labySize - 1; j++ )
         if ( rand() % 4 ) laby[i][j].status = AVAILABLE; //75%的格点为空可用
   startCell = &laby[rand() % ( labySize-2 ) + 1][rand() % ( labySize-2 ) + 1];
   goalCell  = &laby[rand() % ( labySize-2 ) + 1][rand() % ( labySize-2 ) + 1];
   startCell->status = goalCell->status = AVAILABLE; //起始格点必须可用
}


// 输出某一迷宫格的信息
void printLabyCell ( Cell* elem ) {
   printf ( "%d -> (%d, %d) -> %d\n",
            ( ( Cell* ) elem )->incoming,
            ( ( Cell* ) elem )->x,
            ( ( Cell* ) elem )->y,
            ( ( Cell* ) elem )->outgoing );
}


// 显示迷宫
void displayLaby() { //┘└┐┌│─
   static char*  pattern[5][5] = {
      " Ⓢ", " Ⓢ", " Ⓢ", " Ⓢ", " Ⓢ",
      " Ⓢ", "   "," ┌", " ─", " └",
      " Ⓢ", " ┌", "   ", " ┐", " │",
      " Ⓢ", " ─", " ┐", "   ", " ┘",
      " Ⓢ", " └", " │", " ┘", "   "
   };
   printf ( "  " );
   for ( int j = 0; j < labySize; j++ )
      ( j < 10 ) ? printf ( "%2X", j ) : printf ( " %c", 'A' - 10 + j );
   printf ( "\n" );
   for ( int j = 0; j < labySize; j++ ) {
      ( j < 10 ) ? printf ( "%2X", j ) : printf ( " %c", 'A' - 10 + j );
      for ( int i = 0; i < labySize; i++ )
         if ( goalCell == &laby[i][j] )
            printf ( " $" );
         else
            switch ( laby[i][j].status ) {
               case WALL:  printf ( " ■" );   break;
               case BACKTRACKED: printf ( " ○" );   break;
               case AVAILABLE: printf ( "  " );   break;
               default   : printf ( "%s", pattern[laby[i][j].outgoing][laby[i][j].incoming] );   break;
            }
      printf ( "\n" );
   }//for
}//displayLaby


inline Cell* neighbor ( Cell* cell ) { //查询当前位置的相邻格点
   switch ( cell->outgoing ) {
      case EAST  : return cell + LABY_MAX; //向东
      case SOUTH : return cell + 1;        //向南
      case WEST  : return cell - LABY_MAX; //向西
      case NORTH : return cell - 1;        //向北
      default    : exit ( -1 );
   }
}


inline Cell* advance ( Cell* cell ) { //从当前位置转入相邻格点
   Cell* next;
   switch ( cell->outgoing ) {
      case EAST:  next = cell + LABY_MAX; next->incoming = WEST;  break; //向东
      case SOUTH: next = cell + 1;        next->incoming = NORTH; break; //向南
      case WEST:  next = cell - LABY_MAX; next->incoming = EAST;  break; //向西
      case NORTH: next = cell - 1;        next->incoming = SOUTH; break; //向北
      default : exit ( -1 );
   }
   return next;
}


// 迷宫寻径算法：在格单元s至t之间规划一条通路（如果的确存在）
bool labyrinth ( Cell Laby[LABY_MAX][LABY_MAX], Cell* s, Cell* t ) {
      if ( ( AVAILABLE != s->status ) || ( AVAILABLE != t->status ) ) return false; //退化情况
      Stack<Cell*> path; //用栈记录通路（Theseus的线绳）
      s->incoming = UNKNOWN; s->status = ROUTE; path.push ( s ); //起点
      do { //从起点出发不断试探、回溯，直到抵达终点，或者穷尽所有可能
         Cell* c = path.top(); //检查当前位置（栈顶）
         if ( c == t ) {
               displayLaby(); // 若已抵达终点，则找到了一条通路
               return true; // 否则，沿尚未试探的方向继续试探
         }
         while ( NO_WAY > ( c->outgoing = nextESWN ( c->outgoing ) ) ) //逐一检查所有方向
               if ( AVAILABLE == neighbor ( c )->status ) break; //试图找到尚未试探的方向
         if ( NO_WAY <= c->outgoing ) //若所有方向都已尝试过
               { c->status = BACKTRACKED; c = path.pop(); }//则向后回溯一步
         else //否则，向前试探一步
               { path.push ( c = advance ( c ) ); c->outgoing = UNKNOWN; c->status = ROUTE; }
      } while ( !path.empty() );
      displayLaby();
      return false;
}


int main ( int argc, char* argv[] ) {
    srand ( ( unsigned int ) time ( NULL ) ); //设置随机种子
    randLaby(); //使用指定迷宫文件，或随机生成
    //启动算法
    labyrinth ( laby, startCell, goalCell ) ? printf ( "\nRoute found\a\n" ) :printf ( "\nNo route found\a\n" );
    getchar();
    return 0;
}