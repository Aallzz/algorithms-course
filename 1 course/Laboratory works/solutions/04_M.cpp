#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "salesman"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = 20;
const long long inf = (long long)1e16 + 10;
 
int n, m;
long long f[(1 << N)][N], d[N][N];
 
int main()
{
    ios_base::sync_with_stdio(false);
 
    #ifndef Alex_PKZDL
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    cin >> n >> m;
 
    for (int i = 0; i < m; ++i){
        int x, y, w; cin >> x >> y >> w; x--; y--;
        d[x][y] = d[y][x] = w;
    }
 
    for (int mask = 1; mask < (1 << n); mask++)
        for (int i = 0; i < n; ++i){
            if (__builtin_popcount(mask) != 1) f[mask][i] = inf;
            if (mask & (1 << i)){
                int prevMask = mask ^ (1 << i);
                for (int j = 0; j < n; ++j){
                    if ((prevMask & (1 << j)) && d[i][j] != 0)
                        f[mask][i] = min(f[mask][i], f[prevMask][j] + d[i][j]);
                }
            }
        }
 
    long long ans = inf;
    for (int i = 0; i < n; ++i)
        ans = min(ans, f[(1 << n) - 1][i]);
 
    cout << (ans == inf ? -1 : ans) << endl;
    return 0;
}
