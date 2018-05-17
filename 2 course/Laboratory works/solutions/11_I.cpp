#include <bits/stdc++.h>
 
using namespace std;
 
#define std_input_output
 
#ifndef std_input_output
    #define taskname ""
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr int inf {1666666};
constexpr size_t N {1333};
 
struct edge {
    int from, to;
    int cap, cost, flow, id;
 
    edge(int from, int to, int cap, int cost, int flow, int id)
        : from(from), to(to), cap(cap), cost(cost), flow(flow), id(id) {};
};
 
vector<edge> e;
int n, k, s, t;
long long d[N];
int p[N];
vector<int> g[N];
 
void add_edge(int from, int to, int cap, int cost) {
    g[from].push_back((int)e.size());
    e.emplace_back(from, to, cap , cost, 0, e.size());
    g[to].push_back((int)e.size());
    e.emplace_back(to, from, 0, -cost, 0, e.size());
}
 
bool solve() {
    fill_n(d, n, numeric_limits<long long>::max());
    fill_n(p, n, -1);
    d[s] = 0;
    while (true) {
        bool was_update = false;
        for (edge const& cur : e) {
            if (d[cur.from] != numeric_limits<long long>::max()) {
                if (d[cur.to] > d[cur.from] + cur.cost && cur.flow < cur.cap) {
                    was_update = true;
                    d[cur.to] = d[cur.from] + cur.cost;
                    p[cur.to] = cur.id;
                }
            }
        }
        if (!was_update) break;
    }
 
    if (d[t] == numeric_limits<long long>::max()) return 0;
 
    int cur_flow = inf;
    for (int v = p[t]; v != -1; v = p[e[v].from])
        cur_flow = min(cur_flow, e[v].cap - e[v].flow);
    for (int v = p[t]; v != -1; v = p[e[v].from])
        e[v].flow += cur_flow, e[v ^ 1].flow -= cur_flow;
    return cur_flow;
}
 
int matching1[N];
bool used[N];
 
bool dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int cur_id : g[v]) {
        edge& cur = e[cur_id];
        if (cur.flow == 0) continue;
        if (cur.id & 1) continue;
            if (matching1[cur.to] == -1 || dfs(e[matching1[cur.to]].from)) {
                matching1[cur.to] = cur.id;
                return true;
            }
 
    }
    return false;
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
 
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int cost {};
            cin >> cost;
            add_edge(i, j + n, 1, cost);
        }
        add_edge(0, i, k, 0);
        add_edge(i + n, n + n + 1, k, 0);
    }
 
 
    s = 0, t = n + n + 1;
    n = n + n + 2;
    long long ans = 0ll;
    for (; solve(); ) {}
    for (edge const& cur : e)
        if (cur.id & 1) ans += 1ll * cur.cost * cur.flow;
 
    cout << ans << endl;
 
    n = (n - 1) / 2;
    for (int i = 0; i < k; ++i) {
        fill_n(matching1, n + n + 1, -1);
        for (int j = 1; j <= n; ++j) {
            fill_n(used, n + n + 1, false);
            dfs(j);
        }
        vector<int> ans(n, -1);
        for (int j = 1; j <= n; ++j) {
            if (matching1[j + n] == -1) continue;
            edge& cur = e[matching1[j + n]];
            cur.flow = 0;
//            cout << cur.from << " " << cur.to - n << "\n";
            ans[cur.from - 1] = cur.to - n;
        }
        for (int x : ans) cout << x << " ";
        cout << endl;
    }
    return 0;
}
