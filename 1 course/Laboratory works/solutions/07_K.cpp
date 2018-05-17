#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "lca"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = (int)6e5 + 10;
constexpr int inf = (int)1e9 + 10;
constexpr int LG = 20;
struct query_type {
    int a, b;
};
 
vector<query_type> q;
vector<int> g[N];
 
int n;
int tin[N], tout[N], timer;
int anc[LG][N];
 
void dfs(int v, int prev = 0) {
    tin[v] = ++timer;
    anc[0][v] = prev;
    for (int i = 1; i < LG; ++i) {
        anc[i][v] = anc[i - 1][anc[i - 1][v]];
    }
    for (int i = 0; i < (int)g[v].size(); ++i) {
        int to = g[v][i];
        if (to == prev) continue;
        dfs(to, v);
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
    for (int i = 0; i < n; ++i) {
        string tp; cin >> tp;
        if (tp[0] == 'A') {
            int x, y; cin >> x >> y; x--; y--;
            g[x].push_back(y);
            g[y].push_back(x);
        } else {
            int x, y; cin >> x >> y; x--; y--;
            q.push_back({x, y});
        }
    }
 
    dfs(0);
 
    for (int i = 0; i < (int)q.size(); ++i) {
        cout << get_lca(q[i].a, q[i].b) + 1 << "\n";
    }
    return 0;
}
