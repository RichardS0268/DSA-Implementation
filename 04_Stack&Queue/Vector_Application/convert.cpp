/*
利用栈实现数值转换，convert函数中n为要转换的十进制数，base为数值，如2,16等，
*/
#include "../Stack.h"
#include <iostream>
using namespace std;

void convert(Stack<char> &S, int n, int base){
    char digit[] = "01";
    //char digit[] = "0123456789ABCDEF";
    while (n>0){
        S.push(digit[ n % base]);
        n /= base;
    }
}

int main(){
    Stack<char> S;
    int base = 2;
    int n = 7;
    convert(S, n, base);
    while (!S.empty()){
        printf("%c", S.pop());
    }
    printf("\n");
    return 0;
}