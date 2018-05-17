#include <bits/stdc++.h>
      
using namespace std;
 
#define std_input_output
      
#ifndef std_input_output
    #define taskname ""
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr size_t N {522};
constexpr long long inf {1999999999ll*14444};
 
struct edge {
    int from, to;
    long long cap, flow;
    int id;
 
    edge(int from, int to, long long cap, long long flow, int id) 
        : from{from}, to{to}, cap{cap}, flow{flow}, id{id} {}
};
 
vector<edge> e;
vector<int> g[N];
queue<int> q;
int d[N], ptr[N], s, t, n, m;
 
void add_edge(int from, int to, long long cap) {
    g[from].push_back((int)e.size());
    e.emplace_back(from, to, cap, 0, e.size());
    g[to].push_back((int)e.size());
    e.emplace_back(to, from, 0, 0, e.size());
}
 
void gc(int n) {
    while (!q.empty()) q.pop();
    fill_n(d, n, -1);
}
 
bool bfs() {
    gc(n);
    q.push(s);
    d[s] = 0;
    while (!q.empty() && d[t] == -1) {
        int v = q.front();
        q.pop();
        for (int e_id : g[v]) {
            edge const& cur = e[e_id];
            if (d[cur.to] == -1 && cur.flow < cur.cap) {
                q.push(cur.to);
                d[cur.to] = d[cur.from] + 1;
            }
        }
    }
    return d[t] != -1;
}
 
long long dfs(int v, long long flow) {
    if (!flow) return 0ll;
    if (v == t) return flow;
    for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
        edge& cur = e[g[v][ptr[v]]];
        if (d[cur.to] != d[cur.from] + 1) continue;
        long long pushed = dfs(cur.to, min(flow, cur.cap - cur.flow));
        if (pushed) {
            cur.flow += pushed;
            e[cur.id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}
 
 long long solve() {
    long long flow {};
    while (bfs()) {
        fill_n(ptr, n, 0);
        while (long long pushed = dfs(s, inf)) flow += pushed;
    }
    return flow;
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
     
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y, w; cin >> x >> y >> w; x--; y--;
        add_edge(x, y, w);
        add_edge(y, x, w);
    }
    s = 0;
    t = n - 1;
    solve();
    int cnt = 0;
    for (int i = 0; i < n; ++i) cnt += (d[i] != -1);
    cout << cnt << endl;
    for (int i = 0; i < n; ++i) {
        if (d[i] != -1) cout << i + 1 << " ";
    }
    cout << endl;
     
}
