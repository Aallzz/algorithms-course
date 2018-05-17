#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "sparse"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = (int)1e6 + 10;
constexpr int LG = 18;
 
int n, a[LG][N], m;
int lg_table[N];
 
int u, v;
 
int main() {
    ios_base::sync_with_stdio(false);
 
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    cin >> n >> m >> a[0][1];
    for (int i = 2; i <= n; ++i) {
        a[0][i] = (23 * a[0][i - 1] + 21563) % 16714589;
    }
 
    lg_table[1] = 0;
    for (int i = 2; i <= n; ++i) {
        lg_table[i] = lg_table[i / 2] + 1;
    }
 
    for (int lg = 1; lg < LG; ++lg) {
        for (int i = 1, j = (1 + (1 << (lg - 1))); i <= n; ++i, j = min(j + 1, n)) {
            a[lg][i] = min(a[lg - 1][i], a[lg - 1][j]);
        }
    }
 
 
    cin >> u >> v;
    int ans = 0;
    int l = 0;
    int clg;
    for (int i = 1; i <= m; ++i) {
        if (u < v) {
            l = v - u + 1;
            clg = lg_table[l];
            assert(v - (1 << clg) + 1 >= 1 && v - (1 << clg) < n);
            assert(clg >= 0 && clg < 19);
            assert(u > 0 && u <= n);
            ans = min(a[clg][u], a[clg][v - (1 << clg) + 1]);
        } else {
            l = u - v + 1;
            clg = lg_table[l];
            assert(u - (1 << clg) + 1 >= 1 && u - (1 << clg) < n);
            assert(clg >= 0 && clg < 19);
            assert(v > 0 && v <= n);
            ans = min(a[clg][v], a[clg][u - (1 << clg) + 1]);
        }
        if (i != m) {
            u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
            v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
        }
 
    }
 
    cout << u << " " << v << " " << ans << endl;
    return 0;
}
