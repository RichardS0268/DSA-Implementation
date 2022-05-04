#include "Vector.h"
#include "util.h"
#include <iostream>
using namespace std;

#define Rank int
int testID = 0; //测试编号

/******************************************************************************************
 * 测试：无序向量的（顺序）查找
 ******************************************************************************************/
template <typename T> void TestFind ( Vector<T> & V ) {
   for ( Rank i = 0; i < V.size(); i++ ) { //依次查找向量中元素，当然成功
      T e =  V[i]; print ( e );
      Rank r = V.find ( e );
      if ( -1 < r) printf ( " : found at rank V[%d] = %d", r, V[r] );
      else printf ( " : not found until rank V[%d] <> %d", r, e );
      printf ( "\n" );
   }
   for ( Rank i = 0; i <= V.size(); i++ ) { //依次查找每对相邻元素的均值，可能成功
      T a = ( 0 < i ) ? V[i - 1] : V[0] - 4;
      T b = ( i < V.size() ) ? V[i] : V[V.size()-1] + 4;
      T e =  ( a + b ) / 2; print ( e );
      Rank r = V.find ( e );
      if ( -1 < r ) printf ( " : found at rank V[%d] = %d", r, V[r] );
      else printf ( " : not found until rank V[%d] <> %d", r, e );
      printf ( "\n" );
   }
}

/******************************************************************************************
 * 测试：有序向量的查找（binSearch或insertSearch）
 ******************************************************************************************/
template <typename T> void TestSearch ( Vector<T> & V ) {
   for ( Rank i = 0; i < V.size(); i++ ) { //依次查找向量中元素，当然成功
      T e =  V[i]; print ( e ); printf(": by ");
      Rank r = V.search ( e );
      if ( V[r] == e ) printf ( "found at rank V[%d] = %d", r, V[r] );
      else printf ( "found at rank V[%d] = %d <> %d\a\a", r, V[r], e );
      printf ( "\n\n" );
   }
   for ( Rank i = 0; i <= V.size(); i++ ) { //依次相邻元素的均值，可能成功
      T a = ( 0 < i ) ? V[i - 1] : V[0] - 4;
      T b = ( i < V.size() ) ? V[i] : V[V.size()-1] + 4;
      T e =  ( a + b ) / 2; print ( e ); printf(": by ");
      Rank r = V.search ( e );
      printf ( "V[%3d] =", r ); ( r < 0 ) ? print ( "-INF" ) : print ( V[r] ); printf ( "  ~  " );
      printf ( "V[%3d] =", r + 1 ); ( r + 1 < V.size() ) ? print ( V[r + 1] ) : print ( "+INF" );
      bool ordered = true;
      if ( ( r >= 0 ) && ( V[r] > e ) ) ordered = false;
      if ( ( r + 1 < V.size() ) && ( V[r + 1] <= e ) ) ordered = false;
      if ( !ordered ) printf ( "\tincorrect search\a\a" );
      printf ( "\n\n" );
   }
}

/******************************************************************************************
 * 测试：有序向量的插入
 ******************************************************************************************/
template <typename T> //元素类型
void TestOrderedInsertion ( Vector<T> & V, Rank n ) {
   while ( n * 2 > V.size() ) {
      T e = dice ( ( T ) n * 2 );
      printf ( "Inserting " ); print ( e ); printf ( " by " );
      V.insert ( V.search ( e ) + 1, e );
      print ( V );
   }
}

/******************************************************************************************
 * 测试向量
 ******************************************************************************************/
#define PRINT(x)  { print(x); crc(x); checkOrder(x); }
template <typename T> //元素类型
void  testVector ( int testSize ) {
   printf ( "\n  ==== Test %2d. Generate a random vector\n", testID++ );
   Vector<T> V;
   for ( int i = 0; i < testSize; i++ ) V.insert ( dice ( i + 1 ), dice ( ( T ) testSize * 3 ) ); //在[0, 3n)中选择n个数，随机插入向量
   PRINT ( V );
   permute ( V );
   PRINT ( V )
   printf ( "\n  ==== Test %2d. Lowpass on\n", testID++ ); PRINT ( V );
   int i = V.size(); while ( 0 < --i ) { V[i-1] *= 7; V[i-1] += V[i]; V[i-1] >>= 3; }    PRINT ( V );
   printf ( "\n  ==== Test %2d. Increase\n", testID++ ); PRINT ( V );
   increase ( V ); PRINT ( V );
   printf ( "\n  ==== Test %2d. FIND in\n", testID++ ); PRINT ( V );
   TestFind<T> ( V );
   printf ( "\n  ==== Test %2d. Sort degenerate intervals each of size 1 in\n", testID++ ); PRINT ( V );
   for ( Rank i = 0; i < V.size(); i += V.size() / 5 ) { V.sort ( i, i+1 ); PRINT ( V ); } //element by element
   Rank trunk = int(ceil(V.size()/5.0));
   printf ( "\n  ==== Test %2d. Sort %d intervals each of size <=%d in\n", testID++, V.size()/trunk, trunk ); PRINT ( V );
   for ( Rank i = 0; i < V.size(); i += trunk ) { V.sort ( i, min ( V.size(), i + trunk ) ); PRINT ( V ); printf("[%d , %d)\n", i, min ( V.size(), i + V.size() / 5 ) ); } //interval by interval
   printf ( "\n  ==== Test %2d. Sort the entire vector of\n", testID++ ); PRINT ( V );
   V.sort();   PRINT ( V );
   printf ( "\n  ==== Test %2d. FIND in\n", testID++ ); PRINT ( V );
   TestFind<T> ( V );
   printf ( "\n  ==== Test %2d. SEARCH in\n", testID++ ); PRINT ( V );
   TestSearch<T> ( V );
   printf ( "\n  ==== Test %2d. Unsort interval [%d, %d) in\n", testID++, V.size() / 4, 3 * V.size() / 4 ); PRINT ( V );
   V.unsort ( V.size() / 4, 3 * V.size() / 4 );   PRINT ( V );
   printf ( "\n  ==== Test %2d. Unsort interval [%d, %d) in\n", testID++, 0, V.size() ); PRINT ( V );
   V.unsort();   PRINT ( V );
   printf ( "\n  ==== Test %2d. Copy interval [%d, %d) from\n", testID++, V.size() / 4, 3 * V.size() / 4 ); PRINT ( V );
   Vector<T> U ( V, V.size() / 4, 3 * V.size() / 4 );
   PRINT ( U );
   printf ( "\n  ==== Test %2d. Copy from\n", testID++ ); PRINT ( V );
   Vector<T> W ( V );
   PRINT ( W );
   printf ( "\n  ==== Test %2d. Clone from\n", testID++ ); PRINT ( U );
   W = U;
   PRINT ( W );
   printf ( "\n  ==== Test %2d. Remove redundancy in unsorted\n", testID++ ); PRINT ( V );
   printf ( "%d node(s) removed\n", V.deduplicate() );   PRINT ( V );
   printf ( "\n  ==== Test %2d. Sort the entire vercot of\n", testID++ ); PRINT ( V );
   V.sort();   PRINT ( V );
   printf ( "\n  ==== Test %2d. Remove redundancy in sorted\n", testID++ ); PRINT ( V );
   printf ( "%d node(s) removed\n", V.uniquify() );   PRINT ( V );
   printf ( "\n  ==== Test %2d. FIND in\n", testID++ ); PRINT ( V );
   TestFind<T> ( V );
   printf ( "\n  ==== Test %2d. SEARCH & INSERT in\n", testID++ ); PRINT ( V );
   TestOrderedInsertion<T> ( V, testSize );  PRINT ( V );
   printf ( "\n  ==== Test %2d. Remove redundancy in sorted\n", testID++ ); PRINT ( V );
   printf ( "%d node(s) removed\n", V.uniquify() );   PRINT ( V );
}

/******************************************************************************************
 * 测试向量
 ******************************************************************************************/
int main ( int argc, char* argv[] ) {
   if ( 2 > argc ) { printf ( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
   srand ( ( unsigned int ) time ( NULL ) ); //设置随机种子
   testVector<int> ( atoi ( argv[1] ) ); //元素类型可以在这里任意选择
   return 0;
}