#include <iostream>
using namespace std;

template <typename T>
static int BinSearch_A(T *S, T const & e, int lo, int hi){
    while (lo < hi){
        int mi = (lo + hi) >> 1;
        if (e < S[mi]) hi = mi; //深入前半段
        else if (S[mi] < e) lo = mi+1; //深入后半段
        else return mi;//命中
    }
    return -1; //查找失败
}

template <typename T>
static int BinSearch_C(T *S, T const & e, int lo, int hi){
    while (lo < hi){
        int mi = (lo + hi) >> 1;
        e < S[mi] ? hi = mi : lo = mi + 1; //深入前半段
    }
    return lo - 1; //查找失败,返回停止位置，可用作插入操作
}

int main(){
    int A[8] = { 4,7,9,12,15,34,36,67 };
    cout << BinSearch_A<int>(A, 30, 0, sizeof(A)/sizeof(int)-1) << endl;
    cout << BinSearch_C<int>(A, 30, 0, sizeof(A)/sizeof(int)-1) << endl;
    return 0;
}
