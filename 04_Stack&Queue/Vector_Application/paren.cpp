/*
--括号匹配判断
  例: a / (b[i-1][j+1]) + c [i+1][j-1])*2 --> Error
  例：a / (b[i-1][j+1] + c [i+1][j-1])*2  --> Approximately Paired
*/

#include <iostream>
#include <cstring>
#include <iostream>
#include "../Stack.h"
using namespace std;

bool paren ( const char exp[], int lo, int hi ) { //表达式括号匹配检查，可兼顾三种括号
   Stack<char> S; //使用栈记录已发现但尚未匹配的左括号
   for ( int i = lo; i <= hi; i++ ) /* 逐一检查当前字符 */
      switch ( exp[i] ) { //左括号直接进栈；右括号若与栈顶失配，则表达式必不匹配
         case '(': case '[': case '{': S.push ( exp[i] ); break;
         case ')': if ( ( S.empty() ) || ( '(' != S.pop() ) ) return false; break;
         case ']': if ( ( S.empty() ) || ( '[' != S.pop() ) ) return false; break;
         case '}': if ( ( S.empty() ) || ( '{' != S.pop() ) ) return false; break;
         default: break; //非括号字符一律忽略
   }
   return S.empty(); //最终栈空，当且仅当匹配
}

int main(){
    char exp[1000]; //表达式最大长度为1000
    printf("Key in Expression\n");
    char c = getchar();
    int len = 0;
    while (c != '\n'){
        exp[len++] = c;
        c = getchar();
    }
    string output;
    paren(exp, 0, len) ? output = "Approximately Paired" : output = "Error";
    printf("%s\n", output.c_str());
    return 0; 
}