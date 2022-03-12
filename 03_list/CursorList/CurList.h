#ifndef __CURLIST__
#define __CURLIST__
#include <iostream>
using namespace std;
 
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
#define CursorSpace 100
#define Position int
 
void InitializeCursorList(void);
List MakeEmpty(List L);
int isEmpty(List L);
int isLast(List L, Position P);
template<typename T> void Insert(List L, Position P, T X);
template<typename T> void Delete(List L, T X);
template<typename T> Position Find(List L, T X);
template<typename T> Position FindPrevious(List L, T X);
void DeleteList(List L);
 
template<typename T> 
struct Node{
    T X;
    Position Next;
};
 
struct Node<int> CursorList[CursorSpace];
 
int isEmpty(List L){
    return CursorList[L].Next == 0;
}
 
int isLast(List L, Position P){
    return CursorList[P].Next == 0;
}
 
void InitializeCursorList(void){
    int i = 0;
    for (i = 0; i < CursorSpace; i++) {
        CursorList[i].Next = i + 1;
    }
    CursorList[CursorSpace - 1].Next = 0;
}
 
Position CursorAlloc(){
    Position P;
    P = CursorList[0].Next;
    CursorList[0].Next = CursorList[P].Next;
    CursorList[P].Next = 0;
    return P;
}
 
void CursorFree(Position P){
    CursorList[P].Next = CursorList[0].Next;
    CursorList[0].Next = P;
}
 
template<typename T>
Position Find(List L, T X){
    Position P = CursorList[L].Next;
    while (CursorList[P].X != X && P) {
        P = CursorList[P].Next;
    }
    if (P == 0) {
        return false;
    }
    return P;
}
 
template<typename T>
Position FindPrevious(List L, T X){
    Position P = L;
    Position tmp = CursorList[P].Next;
    while (CursorList[tmp].X != X && tmp) {
        tmp = CursorList[tmp].Next;
        P = CursorList[P].Next;
    }
    return P;
}
 
template<typename T>
void Delete(List L, T X){
    Position P = FindPrevious(L, X);
    Position tmp = CursorList[P].Next;
    CursorList[P].Next = CursorList[tmp].Next;
}
 
template<typename T>
void Insert(List L, Position P, T X){
    Position tmp;
    tmp = CursorAlloc();
    CursorList[tmp].X = X;
    CursorList[tmp].Next = CursorList[P].Next;
    CursorList[P].Next = tmp;
}
 
void DeleteList(List L){
    Position P = CursorList[L].Next;
    Position tmp = P;
    while (tmp != 0) {
        P = CursorList[P].Next;
        CursorFree(tmp);
        if (P == 0) {
            break;
        }
        tmp = P;
    }
    CursorList[L].Next = 0;
}
 
void Print(List L){
    Position P = CursorList[L].Next;
    while (P != 0) {
        printf("%d ",CursorList[P].X);
        P = CursorList[P].Next;
    }
    
    printf("\n");
}
 
#endif
