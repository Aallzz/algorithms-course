nclude <bits/stdc++.h>
 
using namespace std;
 
constexpr size_t N {222};
constexpr size_t inf {(long long)1e6 + 10};
 
long long d[N][N];
int n, m;
 
int main() {
 
#ifdef Alex_PKZDL
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#endif
 
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            d[i][j] = inf;
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        --x; --y;
        d[x][y] = w;
    }
 
    for (int i = 0; i < n; ++i)
        d[i][i] = 0;
 
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
 
    string ans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans += to_string(d[i][j]) + " ";
        }
        ans += "\n";
    }
    printf("%s", ans.c_str());
    return 0;
}
