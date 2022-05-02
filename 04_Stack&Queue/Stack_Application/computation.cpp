#include <iostream>
#include <cstring>
#include <cmath>
#include "../Stack.h"
using namespace std;
#define N_OPTR 9 //运算符总数
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //运算符集合
//加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
   /*              |-------------------- 当 前 运 算 符 --------------------| */
   /*              +      -      *      /      ^      !      (      )      \0 */
   /* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
   /* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
   /* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
   /* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
   /* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
   /* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
   /* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
   /* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
   /* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};


void readNumber ( char*& p, Stack<double>& stk ) { //将起始于p的子串解析为数值，并存入操作数栈
    stk.push ( ( double ) ( *p - '0' ) ); //当前数位对应的数值进栈
    while ( isdigit ( * ( ++p ) ) ) //若有后续数字（多位整数），则
        stk.push ( stk.pop() * 10 + ( *p - '0' ) ); //追加之（可能上溢）
    if ( '.' == *p ) { //若还有小数部分
        double fraction = 1; //则
        while ( isdigit ( * ( ++p ) ) ) //逐位
            stk.push ( stk.pop() + ( *p - '0' ) * ( fraction /= 10 ) ); //加入（可能下溢）
    }
}


Operator optr2rank ( char op ) { //由运算符转译出编号
    switch ( op ) {
        case '+' : return ADD; //加
        case '-' : return SUB; //减
        case '*' : return MUL; //乘
        case '/' : return DIV; //除
        case '^' : return POW; //乘方
        case '!' : return FAC; //阶乘
        case '(' : return L_P; //左括号
        case ')' : return R_P; //右括号
        case '\0': return EOE; //起始符与终止符
        default  : exit ( -1 ); //未知运算符
   }
}


char priority ( char op1, char op2 ) //比较两个运算符之间的优先级
{ return pri[optr2rank ( op1 ) ][optr2rank ( op2 ) ]; }


void append ( char* rpn, double opnd ) { //将操作数接至RPN末尾
    char buf[64];
    if ( ( int ) opnd < opnd ) sprintf ( buf, "%6.2f \0", opnd ); //浮点格式，或
    else                       sprintf ( buf, "%d \0", ( int ) opnd ); //整数格式
    strcat ( rpn, buf ); //RPN加长
}


void append ( char* rpn, char optr ) { //将运算符接至RPN末尾
    int n = strlen ( rpn ); //RPN当前长度（以'\0'结尾，长度n + 1）
    sprintf ( rpn + n, "%c \0", optr ); //接入指定的运算符
}


int facI(int opnd){
    if (opnd == 0) return 1;
    for (int i = opnd - 1; i > 0; i--){
        opnd *= i;
    }
    return opnd;
}

double calcu ( char op, double b ) { //执行一元运算
    switch ( op ) {
        case '!' : return ( double ) facI ( ( int ) b ); //目前仅有阶乘，可照此方式添加
        default  : exit ( -1 );
   }
}


double calcu ( double opnd1, char op, double opnd2 ) {
    switch( op ) {
        case '+' : return opnd1 + opnd2; //加
        case '-' : return opnd1 - opnd2; //减
        case '*' : return opnd1 * opnd2; //乘
        case '/' : return opnd1 / opnd2; //除
        case '^' : return pow(opnd1, opnd2); //乘方
        default  : exit(-1);
    }
}

double evaluate ( char* S, char* RPN ) { //对（已剔除白空格的）表达式S求值，并转换为逆波兰式RPN
    Stack<double> opnd; Stack<char> optr; //运算数栈、运算符栈
    optr.push ( '\0' ); //尾哨兵'\0'也作为头哨兵首先入栈
    while ( !optr.empty() ) { //在运算符栈非空之前，逐个处理表达式中各字符
        if ( isdigit ( *S ) ) { //若当前字符为操作数，则
            readNumber ( S, opnd ); append ( RPN, opnd.top() ); //读入操作数，并将其接至RPN末尾
        } 
        else //若当前字符为运算符，则
            switch ( priority ( optr.top(), *S ) ) { //视其与栈顶运算符之间优先级高低分别处理
                case '<': //栈顶运算符优先级更低时
                optr.push ( *S ); S++; //计算推迟，当前运算符进栈
                break;
                case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
                optr.pop(); S++; //脱括号并接收下一个字符
                break;
                case '>': { //栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
                char op = optr.pop(); append ( RPN, op ); //栈顶运算符出栈并续接至RPN末尾
                if ( '!' == op ) //若属于一元运算符
                    opnd.push ( calcu ( op, opnd.pop() ) ); //则取一个操作数，计算结果入栈
                else { //对于其它（二元）运算符
                    double pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); //取出后、前操作数
                    opnd.push ( calcu ( pOpnd1, op, pOpnd2 ) ); //实施二元计算，结果入栈
                }
                break;
                } 
                default : exit ( -1 ); //逢语法错误，不做处理直接退出
            }//switch
    }//while
    return opnd.pop(); //弹出并返回最后的计算结果
}


char* removeSpace ( char* s ) { //剔除s[]中的白空格
   for ( char *p = s-1, *q = s; (p < s) || *p; *++p = *q++ )
      while ( isspace( *q ) ) q++;
   return s;
}


int main () { 
    while (1) {
        printf("Key in Expression (key in exit to quit)\n");
        char exp[1000]; // 表达式最大输入长度为1000
        char c = getchar();
        int len = 0;
        while (c != '\n') {
            exp[len++] = c;
            c = getchar();
        }
        if (exp[0] == 'e' && exp[1] == 'x' && exp[2] == 'i' && exp[3] == 't') break;
        if (len) {
            char* rpn = new char[len];   rpn[0] = '\0'; //逆波兰表达式（4倍原串长，通常不致溢出）
            double value = evaluate ( removeSpace ( exp ), rpn ); //求值
            cout << "Result is " << value << endl;
            cout << "rpn is " << rpn << endl;
            delete rpn;
        }
        else{
            printf("No Input\n"); // 默认非空输入都是合法的 (后续计算中缝语法错误直接退出)
            continue;
        }

    }
    return 0;
}
