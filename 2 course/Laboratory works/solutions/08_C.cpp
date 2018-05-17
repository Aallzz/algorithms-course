#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "shortpath"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {(size_t)1e5 + 10};
constexpr int inf {(int)1e9 + 10};
 
vector<vector<pair<int, int>>> g;
 
size_t n, m;
int s, t;
int d[N];
bool used[N];
 
int dfs(int v) {
    if (v == t) return 0;
    if (used[v])
        return d[v];
    used[v] = true;
    for (auto to : g[v]) {
        d[v] = min(d[v], dfs(to.first) + to.second);
    }
    return d[v];
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
 
    cin >> n >> m >> s >> t; s--; t--;
    g.resize(n);
    for (size_t i = 0; i != m; ++i) {
        int x, y, w; cin >> x >> y >> w; x--; y--;
        g[x].push_back({y, w});
    }
 
    fill_n(d, n, inf);
    d[t] = 0;
    dfs(s);
 
    if (d[s] < inf / 2) {
        cout << d[s] << endl;
    } else {
        cout << "Unreachable" << endl;
    }
 
    return 0;
}
