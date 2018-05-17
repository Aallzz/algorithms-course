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
int n, m, s, t;
long long d[N];
int p[N];
 
void add_edge(int from, int to, int cap, int cost) {
    e.emplace_back(from, to, cap , cost, 0, e.size());
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
        int x, y, cap, cost;
        cin >> x >> y >> cap >> cost; --x; --y;
        add_edge(x, y, cap, cost);
    }
    s = 0, t = n - 1;
     
    long long ans = 0ll;
    for (; solve(); ) {}
    for (edge const& cur : e) 
        if (cur.id & 1) ans += 1ll * cur.cost * cur.flow;
     
    cout << ans << endl; 
    return 0;
}
