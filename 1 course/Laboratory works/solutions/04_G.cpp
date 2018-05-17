#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "meetings"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = 21;
const int M = 5000;
const int inf = (int)1e9 + 10;
 
const int base = M / 2;
 
int n, k;
int a[M], b[M], c[M];
int f[N][(1 << N)];
int prv[N][(1 << N)];
 
int main()
{
    ios_base::sync_with_stdio(false);
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif
 
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> a[i] >> b[i] >> c[i];
 
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < (1 << n); ++j)
            f[i][j] = -inf, prv[i][j] = -1;
 
    f[0][0] = k;
 
    for (int i = 0; i < n; ++i){
        if (f[0][0] >= a[i] && f[0][0] <= b[i]) f[i][(1 << i)] = f[0][0] + c[i];
    }
 
    for (int mask = 1; mask < (1 << n); ++mask){
        for (int i = 0; i < n; ++i){
            if (f[i][mask] == -inf) continue;
            if (!(mask & (1 << i))) continue;
            for (int j = 0; j < n; ++j){
                if (i == j) continue;
                if (mask & (1 << j)) continue;
                if (f[i][mask] >= a[j] && f[i][mask] <= b[j]){
                        f[j][mask ^ (1 << j)] = f[i][mask] + c[j];
                        prv[j][mask ^ (1 << j)] = i;
                }
            }
        }
    }
 
 
    int mxV = -1, mxM = 0;
    for (int i = 0; i < n; ++i)
        for (int mask = 0; mask < (1 << n); ++mask){
            if (f[i][mask] == -inf) continue;
            if (__builtin_popcount(mxM) < __builtin_popcount(mask)){
                mxM = mask;
                mxV = i;
            }
        }
 
    vector<int> ans;
    while(mxV != -1){
        ans.push_back(mxV);
        int pr = prv[mxV][mxM];
        mxM ^= (1 << mxV);
        mxV = pr;
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) cout << ans[i] + 1 << " ";
    cout << endl;
    return 0;
}
