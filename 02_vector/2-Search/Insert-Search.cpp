#include <iostream>
using namespace std;
//O(loglogn)

template <typename T>
int insertSearch(T* S, T const & e, int lo, int hi) {
    while (lo < hi) {
        int mid = lo + (hi-lo)*(e - A[lo])/(A[hi]-A[lo]);
        e < S[mid] ? hi = mid : lo = mid + 1;
    }
    return lo - 1;
}

int main(){
    int A[8] = { 4,7,9,12,15,34,36,67 };
    cout << insertSearch<int>(A, 30, 0, sizeof(A)/sizeof(int)-1) << endl;
    return 0;
}