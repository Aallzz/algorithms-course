#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "optimalcode"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)5e3 + 10;
const long long inf = (long long)1e18 + 10;
 
int n;
long long w[N][N], f[N][N];
int rp[N][N];
 
string code[N];
string cd;
 
void dfs(int l, int r){
    int k = rp[l][r];
    if (l == r) {
        code[l] = cd;
        return ;
    }
    cd += "0";
    dfs(l, k - 1);
    cd.erase(cd.length() - 1);
 
    cd += "1";
    dfs(k, r);
    cd.erase(cd.length() - 1);
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
            f[i][j] = inf;
 
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> w[i][i], rp[i][i] = i, f[i][i] = 0;
 
    for (int i = 0; i < n; ++i){
        long long sum = w[i][i];
        for (int j = i + 1; j < n; ++j){
            sum += w[j][j];
            w[i][j] = sum;
        }
    }
 
    for (int l = 2; l <= n; ++l){
        for (int i = 0; i + l - 1 < n; ++i){
            int j = i + l - 1;
            for (int k = rp[i][j - 1]; k <= rp[i + 1][j]; ++k){
                    if (w[i][j] + f[i][k - 1] + f[k][j] <= f[i][j]){
                        f[i][j] = w[i][j] + f[i][k - 1] + f[k][j];
                        rp[i][j] = k;
                    }
            }
        }
    }
 
    cout << f[0][n - 1] << endl;
 
    dfs(0, n - 1);
 
    for (int i = 0; i < n; ++i) cout << code[i] << endl;
    return 0;
}
