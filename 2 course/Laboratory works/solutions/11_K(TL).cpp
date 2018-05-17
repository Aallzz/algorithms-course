#include <bits/stdc++.h>
 
using namespace std;
 
#define std_input_output
 
#ifndef std_input_output
    #define taskname ""
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr size_t N {2333};
constexpr int inf {1999999999};
 
struct edge {
    int from, to;
    int cap, flow;
    int id;
 
    edge(int from, int to, int cap, int flow, int id)
        : from{from}, to{to}, cap{cap}, flow{flow}, id{id} {}
 
};
 
vector<int> g[N];
vector<edge> e;
int n, m, s, t, l;
int d[N], ptr[N];
 
void add_edge(int from, int to, int cap) {
    g[from].push_back((int)e.size());
    e.emplace_back(from, to, cap, 0, e.size());
    g[to].push_back((int)e.size());
    e.emplace_back(to, from, 0, 0, e.size());
}
 
int dfs(int v, int flow) {
    if (!flow) return 0;
    if (v == t) return flow;
    for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
        edge& cur = e[g[v][ptr[v]]];
        if (d[cur.to] != d[v] + 1) continue;
        int pushed = dfs(cur.to, min(flow, cur.cap - cur.flow));
        if (pushed) {
            cur.flow += pushed;
            e[cur.id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}
 
int main() {
 
#ifdef HOME
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#else
    #ifndef std_input_output
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif
#endif
    ios_base::sync_with_stdio(false);
 
    cin >> n >> m >> l;
    for (int i = 0; i < n; ++i) cin >> d[i];
    for (int i = 0; i < m; ++i) {
        int x, y, cap; cin >> x >> y >> cap; --x; --y;
        add_edge(x, y, cap);
    }
    for (int i = 0; i < n; ++i) {
        if (d[i] == 1) s = i;
        if (d[i] == l) t = i;
    }
 
    fill_n(ptr, n, 0);
    int flow = 0;
    while (int pushed = dfs(s, inf)) flow += pushed;
 
    for (edge const& cur : e) {
        if (cur.id & 1) continue;
        cout << cur.flow << "\n";
    }
    return 0;
}
