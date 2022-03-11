#include <time.h>
#include "Bitmap.h"
#include "Bitmap_J.h"
#include <iostream>
using namespace std;
#define M 1000000000

int main(){
    clock_t start1 = clock();
    Bitmap B(M);
    clock_t end1 = clock();
    cout << "init time of Bitmap = " << end1 - start1 << " ms" << endl;

    clock_t start2 = clock();
    Bitmap_J BJ(M);
    clock_t end2 = clock();
    cout << "init time of Bitmap_J = " << end2 - start2 << " ms" << endl;
    
    return 0;
}
