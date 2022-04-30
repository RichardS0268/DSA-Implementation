#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "../Stack.h" //栈
using namespace std;
typedef enum {Continuous, Step} RunMode;
#define QUEEN_MAX 20 //皇后最大数量

int nSolu = 0; //解的总数
int nCheck = 0; //尝试的总次数
int N = 0; //棋盘size

struct Queen { //皇后类
   int x, y; //皇后在棋盘上的位置坐标
   Queen ( int xx = 0, int yy = 0 ) : x ( xx ), y ( yy ) {};
   bool operator== ( Queen const& q ) const { //重载判等操作符，以检测不同皇后之间可能的冲突
      return    ( x == q.x ) //行冲突（这一情况其实并不会发生，可省略）
                || ( y == q.y ) //列冲突
                || ( x + y == q.x + q.y ) //沿正对角线冲突
                || ( x - y == q.x - q.y ); //沿反对角线冲突
   } // “冲突”即“相等”
   bool operator!= ( Queen const& q ) const { return ! ( *this == q ); } //重载不等操作符
};


void displayRow ( Queen& q ) { //打印当前皇后（放置于col列）所在行
   printf ( "%2d: ", q.x );
   int i = 0;
   while ( i++ < q.y ) printf ( "[ ]" );
   printf ( "[█]" );
   while ( i++ < N ) printf ( "[ ]" );
   printf ( "%2d\n", q.y );
}


void displayProgress ( Stack<Queen>& S, int nQueen ) { //在棋盘上显示搜查的进展
    N = nQueen; 
    S.traverse (displayRow);
    if ( nQueen <= S.size() )
        cout << " solution::" << nSolu << " found after " << nCheck << " check(s)\a";
    getchar();
}


void placeQueens ( int N ) { //N皇后算法（迭代版）：采用试探/回溯的策略，借助栈记录查找的结果
    Stack<Queen> solu; //存放（部分）解的栈
    Queen q ( 0, 0 ); //从原点位置出发
    do { //反复试探、回溯
        if ( N <= solu.size() || N <= q.y ) { //若已出界，则
            q = solu.pop(); q.y++; //回溯一行，并继续试探下一列
        } 
        else { //否则，试探下一行
            while ( ( q.y < N ) && ( 0 <= solu.find ( q ) ) ) //通过与已有皇后的比对
                { q.y++; nCheck++; } //尝试找到可摆放下一皇后的列
            if ( N > q.y ) { //若存在可摆放的列，则
                solu.push ( q ); //摆上当前皇后，并
                if (N == solu.size()) {
                    displayProgress(solu, N); //部分解已成为全局解
                    nSolu++; //通过全局变量nSolu计数
                }
                q.x++; q.y = 0; //转入下一行，从第0列开始，试探下一皇后
            }
        }
    } while ( ( 0 < q.x ) || ( q.y < N ) ); //所有分支均已或穷举或剪枝之后，算法结束
}


int main ( int argc, char* argv[] ) {
    int nQueen = atoi (argv[argc-1]); //棋盘大小 = 皇后总数
    N = nQueen;
    if ( QUEEN_MAX < nQueen || 1 > nQueen ) { //检查参数
        fprintf ( stderr, "\nUsage: %s [-step] <nQueen(%d)>\n", argv[0], QUEEN_MAX );
        return -1;
    }
    placeQueens ( nQueen ); //启动查找
    cout  << nSolu << " solution(s) found after "
            << nCheck << " check(s) for "
            << nQueen << " queen(s)\n"; //输出解的总数
    return 0;
}