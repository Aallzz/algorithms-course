#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "bicone"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {(size_t)2e4 + 10};
constexpr size_t M {(size_t)2e5 + 10};
 
struct edge {
    int from, to, id;
};
 
int n, m;
vector<vector<edge>> g;
vector<edge> bridges;
 
int up[N], h[N];
bool used[N];
int cmp[N];
bool deleted[M];
 
void ddfs(int v, int c) {
    used[v] = true;
    cmp[v] = c;
    for (edge const& e : g[v]) {
        if (deleted[e.id]) continue;
        if (used[e.to]) continue;
        ddfs(e.to, c);
    }
}
 
 
void dfs(int v, edge prev = {-1, -1, -1}) {
    if (used[v]) return ;
    used[v] = true;
    up[v] = h[v] = (prev.from == -1 ? 0 : h[prev.from] + 1);
    for (edge const& e : g[v]) {
        if (e.id == prev.id) continue;
        dfs(e.to, e);
        up[v] = min(up[v], up[e.to]);
        up[v] = min(up[v], h[e.to]);
    }
    if (up[v] == h[v] && prev.from != -1) {
        bridges.push_back(prev);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
 
#ifdef Alex_PKZDL
    ifstream cin(input_file);
    ofstream cout(output_file);
#else
    ifstream cin(taski);
    ofstream cout(tasko);
#endif
 
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i != m; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        g[x].push_back({x, y, i});
        g[y].push_back({y, x, i});
    }
 
    for (int i = 0; i != n; ++i) {
        if (used[i]) continue;
        dfs(i);
    }
 
    fill_n(used, n, false);
 
    for (edge const& e : bridges)
        deleted[e.id] = true;
 
    int cur_cmp = 0;
    for (int i = 0; i != n; ++i) {
        if (!used[i]) {
            ddfs(i, ++cur_cmp);
        }
    }
 
    cout << cur_cmp << endl;
    for (int i = 0; i < n; ++i) {
        cout << cmp[i] << " ";
    }
    cout << endl;
 
    return 0;
}
