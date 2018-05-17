#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "radixsort"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)1e3 + 10;
 
int n, m, k;
string s[N];
 
int cnt[400][N];
int nm[N];
 
int main()
{
    #ifndef Alex_PKZDL
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif // AlexPKZDL
    ios_base::sync_with_stdio(false);
 
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) nm[i] = i;
 
    for (int ii = 0; ii < k; ++ii){
        int i = m - 1 - ii;
        for (int j = 0; j < n; ++j) cnt[(int)s[nm[j]][i]][++cnt[(int)s[nm[j]][i]][0]] = nm[j];
        int sz = 0;
        for (int j = 0; j < 400; ++j){
            for (int c = 0; c < cnt[j][0]; ++c)
                nm[sz++] = cnt[j][c + 1];
            cnt[j][0] = 0;
        }
    }
 
    for (int i = 0; i < n; ++i) cout << s[nm[i]] << endl;
    return 0;
}
