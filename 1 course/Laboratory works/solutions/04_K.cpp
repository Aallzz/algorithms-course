#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "nice3"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)2e3 + 10;
const long long mod = (long long)1e9;
 
long long n, a[N], f[N][N];
 
int main()
{
    ios_base::sync_with_stdio(false);
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
//        ifstream cin(taski);
//        ofstream cout(tasko);
    #endif
 
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) f[i][i] = 1;
 
    for (int len = 1; len <= n; ++len){
        for (int i = 0; i + len < n; ++i){
            int l = i;
            int r = i + len;
            (f[l][r] = mod + f[l + 1][r] + f[l][r - 1] - (a[l] == a[r] ? -1 : f[l + 1][r - 1])) %= mod;
        }
    }
 
    cout << f[0][n - 1] << endl;
    return 0;
}
