#include<iostream>
#include <cstdlib>
#include <ctime> // 通常用当前时刻设置随机种子
#include "./Skiplist.h"
using namespace std;

template <typename T> 
static void print ( T* x ) {  x ? print ( *x ) : printf ( " <NULL>" );  }
static void print ( int & x ) {printf("%02d", x);}
static void print ( char& x ) {  printf ( "%c", x );  } //字符串特别处理
static int dice ( int range ) { return rand() % range; } //取[0, range)中的随机整数

void p_entry ( Entry<int, char>& e ) //引用
{  printf ( "-<" ); print ( e.key ); printf ( ":" ); print ( e.value ); printf ( ">-" );  }


template <typename T> //元素类型
void P_Quadlist ( Quadlist<T>* q ) { //引用
    printf ( "Quadlist::>size = %03d: ", q->size() ); //基本信息
    if ( q->size() <= 0 ) {  printf ( "\n" ); return;  }
    QuadlistNode<T>* curr = q->first()->pred; //当前层之header
    QuadlistNode<T>* base = q->first(); //当前节点所在
    while ( base->below ) base = base->below; //塔底
    while ( base->pred ) base = base->pred; //底层之header
    for ( int i = 0; i < q->size(); i++ ) { //对于当前层的每一节点
        curr = curr->succ; //curr
        QuadlistNode<T>* proj = curr; //找到与curr对应的
        while ( proj->below ) proj = proj->below; //塔底节点（投影）
        while ( ( base = base->succ ) != proj ) //移动base直到proj，期间不断
            printf ( "--------" ); //延长水平联接线
        p_entry(curr->entry); //最后，输出当前层的当前词条
    }
    printf ( "\n" );
}


template <typename K, typename V> //e、value
void P_Skiplist ( Skiplist<K, V>& s ) { //引用
    void (*fp)(Quadlist<Entry<K, V>>* q); // 使用函数指针
    fp = P_Quadlist<Entry<K, V>>; 
    printf ( "Skiplist::>level = %d; size = %d\n",  s.level(), s.size() ); //基本信息
    s.traverse ( fp ); //通过print()遍历输出所有元素
    printf ( "\n" );
}
 

template <typename K, typename V> //key、value
void testSkiplist ( int n ) {
    Skiplist<K, V> L;
    while ( L.size() < n )
        switch ( rand() % 3 ) {
            case 0: { //查找，成功率 <= 33.3%
                K key = dice ( ( K ) n * 3 ); //[0, 3n)范围内的key
                printf ( "Searching for " ); print ( key ); printf ( " ... " );
                V* pValue = L.get ( key );
                if (pValue) printf ( "found with " ), print ( *pValue );
                else printf ( "Not found" ); 
                printf ( "\n" );
                break;
            }
            case 1: { //删除，成功率 <= 33.3%
                K key = dice ( ( K ) n * 3 ); //[0, 3n)范围内的key
                printf ( "Removing " ); print ( key ); printf ( " ... " );
                L.remove ( key ) ? printf ( "Done\n" ) : printf ( "Entry not exists\n" );
                P_Skiplist ( L );
                break;
            }
            default: {// 插入，成功率 == 100%
                K k = dice ( ( K ) n * 3 ); V v = ( V ) 'A' + dice ( 26 ); //在[0, 2n)*['A'~'Z']范围内的词条
                printf ( "Inserting <" ); print ( k ); printf ( "," ); print ( v ); printf ( "> ... " );
                L.put ( k, v ); printf ( "Done\n" );
                P_Skiplist ( L );
                break;
            }
        }
    while ( L.size() > 0 ) {
        K key = dice ( ( K ) n * 3 ); //[0, 3n)范围内的key
        printf ( "Removing " ); print ( key ); printf ( " ... " );
        L.remove ( key ) ? printf ( "Done\n" ) : printf ( "Entry not exists\n" );
        P_Skiplist ( L );
    }
}


int main ( int argc, char* argv[] ) {
    if ( 2 > argc ) { printf ( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
    srand ( ( unsigned int ) time ( NULL ) );
    testSkiplist<int, char> ( atoi ( argv[1] ) ); //元素类型可以在这里任意选择(需同时更改p_entry中Entry的类型)
    return 0;
}