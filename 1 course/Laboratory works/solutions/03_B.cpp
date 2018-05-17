#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "binsearch"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)1e5 + 10;
 
int a[N], n, l, r, m, q;
 
int LeftsideBinarySearch(int key){
    l = -1, r = n;
    while (r - l > 1){
        m =(l + r) / 2;
        if (a[m] < key) l = m;
        else r = m;
    }
    return (a[r] == key ? r : -2);
}
 
int RightsideBinarySearch(int key){
    l = -1, r = n;
    while (r - l > 1){
        m = (l + r) / 2;
        if (a[m] <= key) l = m;
        else r = m;
    }
    return (a[l] == key ? l : -2);
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
    cin >> q;
    for (int i = 0; i < q; ++i){
        int x; cin >> x;
        cout << LeftsideBinarySearch(x) + 1 << " " <<
                RightsideBinarySearch(x) + 1 << endl;
    }
    return 0;
}
