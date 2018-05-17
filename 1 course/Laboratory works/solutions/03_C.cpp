#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "kth"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)3e7 + 10;
 
int a[N], n, k;
int A, B, C;
 
int kPartition(int l, int r){
    if (l == r) return l;
    int i = l - 1;
    int j = r;
    while (true){
        while (a[++i] < a[r]);
        while (a[r] < a[--j] && j > l);
        if (i >= j) break;
        swap(a[i], a[j]);
    }
    swap(a[i], a[r]);
    return i;
}
 
int getKthElement(int l, int r, int k){
    while (true){
        int m = kPartition(l, r);
        if (k < m){
            r = m - 1;
        } else if (m < k){
            l = m + 1;
        } else
            return a[k];
    }
}
 
int main()
{
    #ifndef Alex_PKZDL
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif // AlexPKZDL
    ios_base::sync_with_stdio(false);
 
    cin >> n >> k;
    cin >> A >> B >> C >> a[0] >> a[1];
    for (int i = 2; i < n; ++i)
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
 
    int Kth = getKthElement(0, n - 1, k - 1);
 
    cout << Kth << endl;
    return 0;
}
