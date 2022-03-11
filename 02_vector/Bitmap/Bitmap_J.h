#ifndef __BITMAP_J__
#define __BITMAP_J__
#include <string.h>
using namespace std;


class Bitmap_J{ //校验环型Bitmap，以空间换时间
private:
    int* F; int N;
    int* T; int top;

public:
    Bitmap_J(int n = 8){
        N = n;
        F = new int[N];
        T = new int[N];
        top = 0;
    }
    ~Bitmap_J(){
        delete[] F;
        delete[] T;
    }
    void set(int k);
    void clear(int k);
    bool test(int k);
    void reset(); //重复利用
};

void Bitmap_J::set(int k){
    if (!test(k)){
        T[top] = k;
        F[k] = top++;
    }
}

bool Bitmap_J::test(int k){
    return (0 <= F[k]) && (F[k] < top) && (k == T[F[k]]);
}

void Bitmap_J::clear(int k){
    if (test(k) && (--top)){
        F[T[top]] = F[k];
        T[F[k]] = T[top];
    } //将T中最后一个元素与要删去的元素交换并维护校验环
}

void Bitmap_J::reset(){
    top = 0; //O(1)时间
}
#endif