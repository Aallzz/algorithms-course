#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "sort"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)3e5 + 10;
 
int a[N], c[N];
int n;
 
void MergeSort(int l, int r){
    if (l + 1 >= r) return ;
    int mid = (l + r) / 2;
    MergeSort(l, mid);
    MergeSort(mid, r);
 
    int k = l;
    int q = mid;
 
    for (int i = l; i < r; ++i){
        if ((k < mid && a[k] < a[q]) || q >= r)
            c[i] = a[k++];
        else
            c[i] = a[q++];
    }
 
    for (int i = l; i < r; ++i){
        a[i] = c[i];
    }
}
 
int main()
{
    #ifndef Alex_PKZDL
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif // AlexPKZDL
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
 
    MergeSort(0, n);
 
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
    return 0;
}
