#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "bigseg"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)3e6 + 10;
 
int a[N];
long long n;
long long p[N], kk, c[N], c1[N], c2[N];
int A, B;
long long ans = 0LL;
 
void MergeSort(int l, int r){
    if (l + 1 >= r) return ;
    int mid = (l + r) / 2;
    MergeSort(l, mid);
    MergeSort(mid, r);
 
    int k = l;
    int q = mid;
 
    for (int i = l; i < mid; ++i) c1[i] = p[i];
    for (int i = mid; i < r; ++i) c2[i] = p[i] - kk;
 
    long long curAns = 0LL;
    for (int i = l; i < r; ++i){
        if ((k < mid && c1[k] <= c2[q]) || q >= r)
            k++;
        else{
            curAns += (long long)(mid - k);
            q++;
        }
    }
 
    ans += curAns;
 
    k = l;
    q = mid;
 
    for (int i = l; i < r; ++i){
        if ((k < mid && p[k] <= p[q]) || q >= r)
 
            c[i] = p[k++];
        else
            c[i] = p[q++];
    }
    for (int i = l; i < r; ++i){
        p[i] = c[i];
    }
}
 
int LeftBinarySearch(int l, int r, long long key){
    l--;
    while (r - l > 1){
        int mid = (l + r) / 2;
        if (p[mid] < key) l = mid;
        else r = mid;
    }
    return r;
}
 
unsigned int cur = 0;
 
unsigned int nextRand24() {
    cur = cur * A + B;
    return cur >> 8;
}
 
unsigned int nextRand32() {
    unsigned int a = nextRand24(), b = nextRand24();
    return (a << 8)^b;
}
 
 
int main()
{
    #ifndef Alex_PKZDL
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif // AlexPKZDL
    ios_base::sync_with_stdio(false);
 
    cin >> n >> kk;
    cin >> A >> B;
 
    for (int i = 0; i < n; ++i) a[i] = nextRand32();
 
    for (int i = 0; i < n; ++i) p[i] = (i == 0 ? 0 : p[i - 1]) + a[i];
 
 
    for (int i = 0; i < n; ++i) if (p[i] < kk) ans++;
 
    MergeSort(0, (int)n);
 
 
    cout << ((n * (n + 1LL)) >> 1LL) - ans << endl;
    return 0;
}
