#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "antiqs"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)7e4 + 10;
 
int n, a[N];
 
int main()
{
    #ifndef Alex_PKZDL
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif // AlexPKZDL
    ios_base::sync_with_stdio(false);
 
    cin >> n;
 
    for (int i = 0; i < n; ++i) a[i] = i + 1;
 
    for (int i = 0; i < n; ++i) swap(a[i], a[i / 2]);
 
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
    cout << endl;
 
    return 0;
}
