#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)1e4 + 10;
 
string s, t;
int n, m;
bool f[N][N], u[N][N];
 
bool solve(int i, int j){
    bool &res = f[i][j];
    if (u[i][j]) return res;
    res = 0;
    u[i][j] = true;
 
    if (i == n && j == m) return res = 1;
    if (i >= n) return res = 0;
    if (j >= m && s[i] == '*') return res = solve(i + 1, j);
    if (i >= n || j >= m) return 0;
 
    if (s[i] == '?') res |= solve(i + 1, j + 1);
    if (s[i] == '*'){
        res |= solve(i + 1, j + 1);
        res |= solve(i + 1, j);
        res |= solve(i, j + 1);
    }
    if (s[i] == t[j]) res |= solve(i + 1, j + 1);
    return res;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
 
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #endif // Alex_PKZDL
 
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            f[i][j] = 0, u[i][j] = 0;
 
    cin >> s >> t;
    n = s.length();
    m = t.length();
 
//    bool ans = solve(0, 0);
 
    f[0][0] = 1;
 
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j){
            if (s[i - 1] == '?') f[i][j] |= f[i - 1][j - 1];
            if (s[i - 1] == '*'){
                f[i][j] |= f[i - 1][j - 1] | f[i - 1][j] | f[i][j - 1];
            }
            if (s[i - 1] == t[j - 1]) f[i][j] |= f[i - 1][j - 1];
        }
        if (s[i - 1] == '*') f[i][0] |= f[i - 1][0];
    }
 
    cout << (f[n][m] == 0 ? "NO" : "YES") << endl;
 
    return 0;
}
