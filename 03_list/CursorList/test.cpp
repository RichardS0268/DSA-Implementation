#include "CurList.h"
#include <iostream>
using namespace std;


int main(int argc, const char * argv[])
{
 
    printf("start ...\n");
    InitializeCursorList();
    List L = CursorAlloc();
    Insert(L, L, 1);
    Insert(L, L, 3);
    Insert(L, L, 5);
    Insert(L, L, 4);
    Print(L);
    Position P = FindPrevious(L, 3);
    printf("%d\n",P);
    Delete(L, 3);
    Print(L);
    DeleteList(L);
    Print(L);
    return 0;
}