nclude <bits/stdc++.h>
 
using namespace std;
 
constexpr long long inf {(long long)1e16 + 10};
constexpr size_t N {(size_t)2e3 + 10};
 
vector<vector<int>> g;
int n, s, f;
int d[N][N];
long long dd[N];
bool used[N];
 
int main() {
 
#ifdef Alex_PKZDL
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#endif
 
    scanf("%d%d%d", &n, &s, &f); --s; --f;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &d[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) dd[i] = inf;
    dd[s] = 0;
    for (int i = 0; i < n; ++i) {
        int cur_v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (cur_v == -1 || dd[cur_v] > dd[j]))
                cur_v = j;
        }
        if (dd[cur_v] == inf) {
            break;
        }
        used[cur_v] = true;
        for (int j = 0; j < n; ++j) {
            if (d[cur_v][j] == -1) continue;
            dd[j] = min(dd[j], dd[cur_v] + d[cur_v][j]);
        }
    }
    printf("%lld\n", dd[f] == inf ? -1 : dd[f]);
    return 0;
}
