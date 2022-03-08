#ifndef __BITMAP__
#define __BITMAP__
#include <string.h>
using namespace std;

class Bitmap{
private:
    int N;
    char * M; // Bitmap所存放的空间为M[], 容量为N*sizeof(char)*8比特
protected:
    void init (int n);

public:
    Bitmap(int n = 8){ // n根据要处理的数据规模进行指定，n=8即存8个数
        init(n);
    }
    ~Bitmap() {
        delete[] M;
        M = NULL;
    }     
    void set(int k);
    void clear(int k);
    bool test(int k);
};

void Bitmap::init(int n){
    M = new char[N = (n+7)/8];
    memset(M, 0, N);
}

void Bitmap::set(int k){
    M[k >> 3] |= (0x80 >> (k & 0x07));
}

void Bitmap::clear(int k){
    M[k >> 3] &= ~(0x80 >> (k & 0x07));
}

bool Bitmap::test(int k){
    return M[k >> 3] & (0x80 >> (k & 0x07));
}


#endif