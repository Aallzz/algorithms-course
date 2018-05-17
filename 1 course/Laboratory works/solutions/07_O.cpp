#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "minonpath"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = (int)2e5 + 10;
constexpr int LG = 19;
constexpr int inf = (int)1e9 + 10;
 
vector<pair<int, int> > g[N];
int n, q;
 
int anc[LG][N], wanc[LG][N];
int tin[N], tout[N], timer;
 
void dfs(int v, int prev = 0, int prevW = inf) {
    tin[v] = ++timer;
    anc[0][v] = prev;
    for (int i = 1; i < LG; ++i) {
        anc[i][v] = anc[i - 1][anc[i - 1][v]];
    }
    wanc[0][v] = prevW;
    for (int i = 1; i < LG; ++i) {
        wanc[i][v] = min(wanc[i - 1][v], wanc[i - 1][anc[i - 1][v]]);
    }
 
    for (int i = 0; i < (int)g[v].size(); ++i) {
        int to = g[v][i].first;
        if (to == prev) continue;
        dfs(to, v, g[v][i].second);
    }
    tout[v] = timer;
}
 
bool ancestor(int a, int b) {
    return (tin[a] <= tin[b] && tout[a] >= tout[b]);
}
 
int get_lca(int a, int b) {
    if (ancestor(a, b)) return a;
    if (ancestor(b, a)) return b;
    for (int i = LG - 1; i >= 0; --i) {
        if (!ancestor(anc[i][a], b)) {
            a = anc[i][a];
        }
    }
    return anc[0][a];
}
 
int get_minW(int a, int b) {
    int res = inf;
    for (int i = LG - 1; i >= 0; --i) {
        if (!ancestor(anc[i][a], b)) {
            res = min(res, wanc[i][a]);
            a = anc[i][a];
        }
    }
    if (!ancestor(a, b)) res = min(res, wanc[0][a]), a = anc[0][a];
    for (int i = LG - 1; i >= 0; --i) {
        if (!ancestor(anc[i][b], a)) {
            res = min(res, wanc[i][b]);
            b = anc[i][b];
        }
    }
    if (!ancestor(b, a)) res = min(res, wanc[0][b]), b = anc[0][b];
    return res;
}
 
int main() {
 
    ios_base::sync_with_stdio(false);
    #ifdef Alex_PKZDL
//        freopen("input.txt", "r", stdin);
//        freopen("output.txt", "w", stdout);
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
//        freopen(taski, "r", stdin);
//        freopen(tasko, "w", stdout);
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    cin >> n;
    for (int i = 1; i <= n - 1; ++i) {
        int x, w; cin >> x >> w; x--;
        g[i].push_back({x, w});
        g[x].push_back({i, w});
    }
 
    dfs(0);
 
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        cout << get_minW(x, y) << "\n";
    }
    return 0;
}
