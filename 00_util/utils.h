#ifndef __UTILS__
#define __UTILS__

#include <cstdio> //采用C风格精细控制输出格式
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <typeinfo>
using namespace std;

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

#if defined(DSA_DEBUG) //编译开关，控制调试输出
#define DSA(x)  { x } //输出
#else
#define DSA(x) //不输出
#endif

template <typename T> struct Show{
    virtual void operator() (T& e) {cout << e << " ";};
};


/* comparator */

template <typename T> static bool lt ( T* a, T* b ) { return lt ( *a, *b ); } //less than
template <typename T> static bool lt ( T& a, T& b ) { return a < b; } //less than
template <typename T> static bool eq ( T* a, T* b ) { return eq ( *a, *b ); } //equal
template <typename T> static bool eq ( T& a, T& b ) { return a == b; } //equal

/* checkOrder */
template <typename T> struct CheckOrder { //函数对象：判断一个T类对象是否局部有序
   T pred; int& u;
   CheckOrder ( int& unsorted, T& first ) : pred ( first ), u ( unsorted ) { }
   virtual void operator() ( T& e ) { if ( pred > e ) u++; pred = e; }
};

/* Decrease */
template <typename T> struct Decrease //函数对象：递减一个T类对象
   {  virtual void operator() ( T& e ) { e--; }  }; //假设T可直接递减或已重载--

/* Double */
template <typename T> struct Double //函数对象：倍增一个T类对象
   {  virtual void operator() ( T& e ) { e *= 2; }  }; //假设T可直接倍增

/* Half */
template <typename T> struct Half //函数对象：减半一个T类对象
   {  virtual void operator() ( T& e ) { e /= 2; }  }; //假设T可直接减半

/* Increase */
template <typename T> struct Increase //函数对象：递增一个T类对象
   {  virtual void operator() ( T& e ) { e++; }  }; //假设T可直接递增或已重载++

/* crc_Elem */
template <typename T> struct Crc { //函数对象：累计T类对象的特征（比如总和），以便校验对象集合
   T& c;
   Crc ( T& crc ) : c ( crc ) {}
   virtual void operator() ( T& e ) { c += e; } //假设T可直接相加
};

/******************************************************************************************
 * 在[0, range)内随机生成一个数
 ******************************************************************************************/
int dice ( int range ) { return rand() % range; } //取[0, range)中的随机整数
int dice ( int lo, int hi ) { return lo + rand() % ( hi - lo ); } //取[lo, hi)中的随机整数
float dice ( float range ) { return rand() % ( 1000 * ( int ) range ) / ( float ) 1000.; }
double dice ( double range ) { return rand() % ( 1000 * ( int ) range ) / ( double ) 1000.; }
char dice ( ) { return ( char ) ( 32 + rand() % 96 ); }


/******************************************************************************************
 * 列表、向量等结构内的节点中，可以存放基本类型或构造类型
 * 按照本书约定，出于效率的考虑，对于后一情况通常只保存对象的指针
 * 因此，在主体结构析构之前，需要首先释放这些成员对象所占的空间
 * 此处，借助C++中偏特化技术区分上述两种情况，并做对应处理
 ******************************************************************************************/

template <typename T> struct Cleaner {
   static void clean ( T x ) { //相当于递归基
#ifdef _DEBUG
      static int n = 0;
      if ( 7 > strlen ( typeid ( T ).name() ) ) { //复杂类型一概忽略，只输出基本类型
         printf ( "\t<%s>[%d]=", typeid ( T ).name(), ++n );
         print ( x );
         printf ( " purged\n" );
      }
#endif
   }
};

template <typename T> struct Cleaner<T*> {
   static void clean ( T* x ) {
      if ( x ) { delete x; } //如果其中包含指针，递归释放
#ifdef _DEBUG
      static int n = 0;
      printf ( "\t<%s>[%d] released\n", typeid ( T* ).name(), ++n );
#endif
   }
};

template <typename T> void release ( T x ) { Cleaner<T>::clean ( x ); }


/******************************************************************************************
 * 数据元素、数据结构通用输出接口
 ******************************************************************************************/


class UniPrint {
public:
   static void p ( int );
   static void p ( float );
   static void p ( double );
   static void p ( char );

   // template <typename K, typename V> static void p ( Entry<K, V>& ); //Entry
   // template <typename T> static void p ( BinNode<T>& ); //BinTree节点
   // template <typename T> static void p ( BinTree<T>& ); //二叉树
   // template <typename T> static void p ( BTree<T>& ); //B-树
   // template <typename T> static void p ( BST<T>& ); //BST
   // template <typename T> static void p ( AVL<T>& ); //AVL
   // template <typename T> static void p ( RedBlack<T>& ); //RedBlack
   // template <typename T> static void p ( Splay<T>& ); //Splay
   // template <typename T> static void p ( Quadlist<T>& ); //Quadlist
   // template <typename K, typename V> static void p ( Skiplist<K, V>& ); //Skiplist
   // template <typename K, typename V> static void p ( Hashtable<K, V>& ); //Hashtable
   // template <typename T> static void p ( PQ_List<T>& ); //PQ_List
   // template <typename T> static void p ( PQ_ComplHeap<T>& ); //PQ_ComplHeap
   // template <typename T> static void p ( PQ_LeftHeap<T>& ); //PQ_LeftHeap
   // template <typename Tv, typename Te> static void p ( GraphMatrix<Tv, Te>& ); //Graph
   template <typename T> static void p ( T& s);//向量、列表等支持traverse()遍历操作的线性结构
   template <typename T> static void p ( T* s ) { s ? p ( *s ) : printf ( "<NULL>" ); } //所有指针统一转为引用
}; //UniPrint

template <typename T> static void print ( T* x ) {  x ? printf ( *x ) : printf ( " <NULL>" );  }
template <typename T> static void print ( T& x ) {  UniPrint::p ( x );  }
template <typename T> static void print ( const T& x ) {  UniPrint::p ( x );  } //for Stack
void print ( char* x ) {  printf ( " %s", x ? x : "<NULL>" );  } //字符串特别处理
void print ( const char* x ) {  printf ( " %s", x ? x : "<NULL>" );  } //字符串特别处理

void UniPrint::p ( int e ) { printf ( " %04d", e ); }
void UniPrint::p ( float e ) { printf ( " %4.3f", e ); }
void UniPrint::p ( double e ) { printf ( " %4.6f", e ); }
void UniPrint::p ( char e ) { printf ( " %c", ( 31 < e ) && ( e < 128 ) ? e : '$' ); }
template<typename T> void UniPrint::p(T& s){
   struct Show<int> B;
   s.traverse(B);
   cout << endl;
}


// void UniPrint::p ( VStatus e ) {
//    switch ( e ) {
//       case UNDISCOVERED:   printf ( "U" ); break;
//       case DISCOVERED:     printf ( "D" ); break;
//       case VISITED:        printf ( "V" ); break;
//       default:             printf ( "X" ); break;
//    }
// }
// void UniPrint::p ( EType e ) {
//    switch ( e ) {
//       case UNDETERMINED:   printf ( "U" ); break;
//       case TREE:           printf ( "T" ); break;
//       case CROSS:          printf ( "C" ); break;
//       case BACKWARD:       printf ( "B" ); break;
//       case FORWARD:        printf ( "F" ); break;
//       default:             printf ( "X" ); break;
//    }
// }

#endif