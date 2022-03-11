#include "Bitmap.h"
#include "Bitmap_J.h"
#include <iostream>
#include<stdio.h>
#include<string.h> 
#include<stdlib.h>

using namespace std;

int main(){
    int n = 50;
    Bitmap B(n);
    B.set(0);
    B.set(1);

    Bitmap_J BJ(n);
    BJ.set(0);
    BJ.set(1);
    for (int i = 2; i < n; i++){
        if (!B.test(i)){
            for (int j = 2*i; j < n; j += i){
                B.set(j);
            }
        }
        if (!BJ.test(i)){
            for (int j = 2*i; j < n; j += i){
                BJ.set(j);
            }
        }
    } //O(n·logn)

    cout << "B: " << endl;
    for (int i = 1; i < n; i ++){
        if (!B.test(i)){
            cout << i << " " ;
        }
    }
    cout << endl;
    
    cout << "BJ: " << endl;
    for (int i = 1; i < n; i ++){
        if (!BJ.test(i)){
            cout << i << " " ;
        }
    }
    cout << endl;
    return 0;
}