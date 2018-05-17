#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "matrix"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)4e2 + 10;
const int inf = (int)1e9 + 10;
 
string fs[N][N];
int f[N][N], a[N][N], b[N][N], n;
 
int solve(int l, int r){
    int &res = f[l][r];
    if (res != -1) return res;
    res = inf;
    for (int k = l; k < r; ++k){
        int curRes = solve(l, k) + solve(k + 1, r);
        curRes += a[l][k] * b[l][k] * b[k + 1][r];
//        cerr << l << " " << r << " " << a[l][k] * b[l][k] * b[k + 1][r] + solve(l, k) + solve(k + 1, r) << " " << res << endl;
        if (curRes < res){
            fs[l][r] = "(" + fs[l][k] + fs[k + 1][r] + ")";
            res = curRes;
            a[l][r] = a[l][k];
            b[l][r] = b[k + 1][r];
        }
    }
    return res;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
 
    #ifndef Alex_PKZDL
        ifstream cin(taski);
        ofstream cout(tasko);
    #else
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #endif // Alex_PKZDL
 
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            f[i][j] = -1;
 
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i][i] >> b[i][i], f[i][i] = 0, fs[i][i] = 'A';
 
//    cout << solve(0, n - 1) << endl;
    solve(0, n - 1);
 
    cout << fs[0][n - 1] << endl;
    return 0;
}
