#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "../Stack.h" //借助栈结构，计算直方图H[]中的最大矩形（并列时取最靠左者）

// 按定义蛮力地计算直方图H[]中的最大矩形（多个并列时取最靠左侧者）
int mr_BRUTE( int H[], int n, int& mr_r, int& mr_s, int& mr_t ) { //蛮力：O(n^2)
    int maxRect = 0;
    // 遍历所有的bar，对每个bar分别（遍历）求左边界，右边界。两层循环，O(n^2)
    for ( int r = 0, s = 0, t = 0; r < n; r++, s = t = r ) {
        do s--; while ( -1 < s  &&  H[s] >= H[r] ); s++;
        do t++; while ( t < n   &&  H[r] <= H[t] );
        int rect = (int) H[r] * ( t - s );
        if ( maxRect < rect )
            { maxRect = rect; mr_r = r; mr_s = s; mr_t = t; }
    }
    return maxRect;
} //每个极大矩形耗时O(n)，累计O(n^2)


// 借助一个栈：O(n)
int mr_STACK( int H[], int n, int& mr_r, int& mr_s, int& mr_t ) { //H[]皆非负
    Stack<int> SR; //次栈顶、栈顶总是s[r]-1与r，当前的t = t[r]
    int maxRect = 0;
    for ( int t = 0; t <= n; t++ ) { //逐个尝试以t为右边界的
        // s(r) = max{ k| 0 <= k < r and H[k-1] < H[r] }
        while ( !SR.empty() && ( t == n || H[SR.top()] > H[t] ) ) { //每一个极大矩形
            int r = SR.pop(); int s = SR.empty() ? 0 : SR.top() + 1;
            int mR = H[r] * ( t - s );
            if ( maxRect < mR )
                { maxRect = mR; mr_r = r; mr_s = s; mr_t = t; }
        }
        if ( t < n ) SR.push( t ); //栈中只记录所有的H[s] = min{ H[k] | s <= k <= t } 
    } //assert: SR is empty at exit
    return maxRect;
} //每项进栈、出栈不过常数次，累计成本O(n)


// 借助两个栈：O(n)
int mr_STACKS( int H[], int n, int& mr_r, int& mr_s, int& mr_t ) { //除末项-1哨兵，H[]皆非负
    int* s = new int[n]; Stack<int> S; //自右可见项的秩
    for( int r = 0; r < n; r++ ) { //依次计算出
        while ( !S.empty() && H[S.top()] >= H[r] ) S.pop(); //每一个s(r)
        s[r] = S.empty() ? 0 : 1 + S.top();
        S.push(r);
    }
    while( !S.empty() ) S.pop();

    int* t = new int[n]; Stack<int> T; //自左可见项的秩
    for( int r = n-1; -1 < r; r-- ) { //依次计算出
        while ( !T.empty() && H[r] <= H[T.top()] ) T.pop(); //每一个t(r)
        t[r] = T.empty() ? n : T.top();
        T.push(r);
    }
    while( !T.empty() ) T.pop();

    int maxRect = 0;
    for( int r = 0; r < n; r++ ) {
        int mR = H[r] * (t[r] - s[r]);
        if ( maxRect < mR )
            { maxRect = mR; mr_r = r; mr_s = s[r]; mr_t = t[r]; }
    }
    delete [] s; delete [] t;
    return maxRect;
} //每项进栈、出栈不过常数次，累计成本O(n)


// 直方图中的最大矩形
int main ( int argc, char* argv[] ) {
    int* H; int n; //宽度为n的直方图
    if ( 1 < argc ) { //命令行指定，比如：77 4 120 16 96 59 0 15 123 8 79 73 57 96 84 101 26 12 88 81 111 18 87 117 46 90 94 70 125
        H = new int[ n = argc -1 ];
        for ( int i = 0; i < n; i++ )
            H[i] = atoi( argv[i+1] );
    } else { //随机生成
        srand ( ( unsigned int ) time ( NULL ) );
        H = new int[ 1 + ( n = rand() % 128 ) ];
        for ( int i = 0; i < n; i++ )
            H[i] = rand() % 128;
    }

    int r, s, t; //最大矩形：H[r] x [s, t)
    int mrBrute = mr_BRUTE( H, n, r = -1, s = -1, t = -1 );
    printf( "MaxRect Brute-Force  : %I64d = %d x [%d,%d)\n", mrBrute, H[r], s, t );
    int mrStacks = mr_STACKS( H, n, r = -1, s = -1, t = -1 );
    printf( "MaxRect using STACKS : %I64d = %d x [%d,%d)\n", mrStacks, H[r], s, t );
    int mrStack  = mr_STACK ( H, n, r = -1, s = -1, t = -1 );
    printf( "MaxRect using STACK  : %I64d = %d x [%d,%d)\n", mrStack, H[r], s, t );

    for ( int i = 0; i < s; i++ ) {
        printf("%3d:%4d : ", i, H[i]);
        for ( int j = 0; j < H[i]; j++ ) printf("."); printf("\n");
    }
    for ( int i = s; i < r; i++ ) {
        printf("%3d:%4d : ", i, H[i]);
        for ( int j = 0; j < H[i]; j++ ) printf( (j < H[r]) ? "#" : "." ); printf("\n");
    }
    {
        printf("%3d:%4d : ", r, H[r]);
        for ( int j = 0; j < H[r]; j++ ) printf("O"); printf("\n");
    }
    for ( int i = r+1; i < t; i++ ) {
        printf("%3d:%4d : ", i, H[i]);
        for ( int j = 0; j < H[i]; j++ ) printf( (j < H[r]) ? "#" : "." ); printf("\n");
    }
    for ( int i = t; i < n; i++ ) {
        printf("%3d:%4d : ", i, H[i]);
        for ( int j = 0; j < H[i]; j++ ) printf("."); printf("\n");
    }

    delete [] H;
    return 0;
}