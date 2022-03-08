# Search

+ Bin-Search_A 将每次查找分为三种情况，包括`_elem[mid] = target`的情况，对此，可以证明当查找的分点为黄金分割比时（$'mid'=\frac{\sqrt{5}-1}{2}$），拥有常数意义上的最低复杂度$O(1.44logn)$，此时也称为Fibonacci查找, 而$'mid'=\frac{1}{2}$时，复杂度为$O(1.5logn)$。
  + 然而Bin-Search_A 并不稳定，有Best case(`_elem[mid] = target` -> $O(1)$)和worst case(target在最后一项 -> $O(2logn)$)，两者之间效率相差很大。
  + 因此我们通常使用Bin_Search_C,它更加**稳定**，复杂度稳定在$O(logn)$水平。
+ 此外，对于较大规模的数据，当其分布较为均匀时，则可使用插值查找的方法
  + 此时[lo, hi]中的元素大致成线性趋势增长，即$$\frac{mi-lo}{hi-lo}\approx\frac{2-A[lo]}{A[hi]-A[lo]}$$
    则可取分点$$mi \approx lo+(hi-lo)·\frac{e-A[lo]}{A[hi]-A[lo]}$$

  + 插值查找的复杂度为$O(loglogn)$