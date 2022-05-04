#include "./CurList_pointer.h"

// 测试游标式列表
void testCursor ( int testSize ) {
    CursorList<char> CL ( testSize ); 
    printf("== Init ==\n");
    CL.print();
    for ( int i = 0; i < testSize ; i++ ) {
        char x = 'A' + ( rand() % 26 );
        if ( 30 < ( rand() % 100 ) ) {
            CL.insert ( x );
            printf ( "== %c inserted at Last ==\n", x );
        } 
        else {
            if ( 0 > CL.find ( x ) )
                printf ( "== %c not found ==\n", x );
            else
                printf ( "== %c removed at %d ==\n", x, CL.remove ( CL.find ( x ) ) );
        }
        CL.print();
    }
    for ( char x = 'A'; x <= 'Z'; x++ ) {
        while ( 0 <= CL.find ( x ) )
            printf ( "== %c removed at %d ==\n", x, CL.remove ( CL.find ( x ) ) );
   }
}

int main ( int argc, char* argv[] ) {
    if ( 2 > argc ) { printf ( "Usage: %s <size of test>\a\a\n", argv[0] ); return 1; }
    srand ( ( unsigned int ) time ( NULL ) ); //设置随机种子
    testCursor ( atoi ( argv[1] ) ); //元素类型可以在这里任意选择
    return 0;
}