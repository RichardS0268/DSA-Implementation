#define Rank int
#include <iostream>
using namespace std;

template <typename T>
Rank insertSearch(T* S, T const & e, Rank lo, Rank hi) {
    while (lo < hi) {
        Rank mid = (lo + hi) >> 1;
        e < S[mid] ? hi = mid : lo = mid + 1;
    }
    return lo - 1;
}

int main(){
    int A[8] = { 4,7,9,12,15,34,36,67 };
    cout << insertSearch<int>(A, 34, 0, sizeof(A)/sizeof(int)-1) << endl;
    return 0;
}

