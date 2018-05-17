#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "invcnt"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)1e6 + 10;
 
int a[N], c[N];
unsigned int n, A, B, m;
long long ans = 0LL;
 
void MergeSort(int l, int r){
    if (l + 1 >= r) return ;
    int mid = (l + r) / 2;
    MergeSort(l, mid);
    MergeSort(mid, r);
 
    int k = l;
    int q = mid;
 
    for (int i = l; i < r; ++i){
        if ((k < mid && a[k] <= a[q]) || q >= r)
            c[i] = a[k++];
        else {
            ans += (long long)(mid - k);
            c[i] = a[q++];
        }
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
    cin >> n >> m;
    cin >> A >> B;
    unsigned int cur = 0;
    for (int i = 0; i < (int)n; ++i){
        cur = cur * A + B;
        a[i] = ((cur >> 8) % m);
    }
    MergeSort(0, (int)n);
 
    cout << ans << endl;
    return 0;
}
