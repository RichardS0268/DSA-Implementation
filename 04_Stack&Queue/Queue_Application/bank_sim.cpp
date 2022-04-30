#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>
#include "../Queue.h"
using namespace std;

struct Customer { int window; unsigned int time; }; //顾客类：所属窗口（队列）、服务时长

// 输出顾客c的状态
void printCustomer ( Customer c )
{ printf ( "%4d", c.time ); }

int calsum(Queue<Customer> window){
   int ss = 0;
   for (int i = window.size(); i > 0; i--){
      ss += window.dequeue().time;
   }
}

int bestWindow ( Queue<Customer> windows[], int nWin ) { //为新到顾客确定最佳队列
   int minSize = calsum(windows[0]), optiWin = 0; //最优队列（窗口）
   for ( int i = 1; i < nWin; i++ ) //在所有窗口中
      if ( minSize > calsum(windows[i]) ) //挑选出
         { minSize = calsum(windows[i]); optiWin = i; } //队列最短者
   return optiWin; //返回
}


// 显示当前各（窗口）队列情况
void displayProgress ( Queue<Customer> windows[], int nWin, int now ) {
   printf ( "============ Time: %4d ============\n", now );
   for ( int i = 0; i < nWin; i++ ) { //对每个窗口，分别
      printf ( "Window #%c:  ", 'A' + i ); //输出窗口编号
      windows[i].traverse ( printCustomer ); printf ( "\n" ); //列出队列中的所有顾客
   }
}


void simulate ( int nWin, int servTime ) { //按指定窗口数、服务总时间模拟银行业务
   Queue<Customer>* windows = new Queue<Customer>[nWin]; //为每一窗口创建一个队列
   for ( int now = 0; now < servTime; now++ ) { //在下班之前，每隔一个单位时间
      if ( rand() % ( 1 + nWin ) ) { //新顾客以nWin/(nWin + 1)的概率到达
         Customer c ; c.time = 1 + rand() % 98; //新顾客到达，服务时长随机确定
         c.window = bestWindow ( windows, nWin ); //找出最佳（最短）的服务窗口
         windows[c.window].enqueue ( c ); //新顾客加入对应的队列
         displayProgress(windows, nWin, now );
      }
      for ( int i = 0; i < nWin; i++ ) //分别检查
         if ( !windows[i].empty() ) //各非空队列
            if ( -- windows[i].front().time <= 0 ) //队首顾客的服务时长减少一个单位
               windows[i].dequeue(); //服务完毕的顾客出列，由后继顾客接替
   } //for
   
   delete [] windows; //释放所有队列（此前，~List()会自动清空队列）
}


//事件模拟
int main ( int argc, char* argv[] ) {
   if ( argc < 3 ) {  printf ( "Usage: %s <nWin> <servTime>\n", argv[0] ); return -1;  }
   srand ( ( unsigned int ) time ( NULL ) ); //设置随机种子
   simulate ( atoi ( argv[1] ), atoi ( argv[2] ) ); //启动模拟
   return 0;
}