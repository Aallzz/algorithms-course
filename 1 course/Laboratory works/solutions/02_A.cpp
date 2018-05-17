#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)1e5 + 10;
 
#define taskname "isheap"
#define taski taskname".in"
#define tasko taskname".out"
 
#ifndef Alex_PKZDL
#define file ifstream cin(taski); ofstream cout(tasko)
//#define file freopen(taski, "r", stdin); freopen(tasko, "w", stdout)
#else
#define file ifstream cin("input.txt"); ofstream cout("output.txt")
//#define file freopen(taski, "r", stdin); freopen(tasko, "w", stdout)
#endif
int a[N], n;
 
int main()
{
    file;
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    bool ok = true;
    for (int i = 0; i < n; ++i){
        if (i + i + 1 < n && a[i + i + 1] < a[i]) ok = false;
        if (i + i + 2 < n && a[i + i + 2] < a[i]) ok = false;
    }
 
    cout << (ok ? "YES" : "NO") << endl;
    return 0;
}
