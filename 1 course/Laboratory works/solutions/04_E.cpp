#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "levenshtein"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)5e3 + 10;
const int inf = (int)1e9 + 10;
 
string s, t;
int n, m;
int f[N][N];
 
int solve(int i, int j){
 
    if (i > n || j > m) return inf;
    if (i == n && j == m) return 0;
 
    int &res = f[i][j];
    if (f[i][j] != -1) return res;
 
    res = inf;
 
    if (i < n && j < m) res = min(res, solve(i + 1, j + 1) + (s[i] != t[j]));
    if (i < n) res = min(res, solve(i + 1, j) + 1);
    if (j < m) res = min(res, solve(i, j + 1) + 1);
 
    return res;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
 
    #ifndef Alex_PKZDL
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            f[i][j] = -1;
 
    cin >> s >> t;
    n = s.length();
    m = t.length();
 
    int ans = solve(0, 0);
 
    cout << ans << endl;
    return 0;
}
