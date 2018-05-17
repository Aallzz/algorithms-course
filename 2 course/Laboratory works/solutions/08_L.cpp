#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "biconv"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {(size_t)2e4 + 10};
constexpr size_t M {(size_t)2e5 * 2 + 10};
 
int n, m;
vector<pair<int, int> > g[N];
bool used[N];
set<pair<int, int>> was;
 
int tin[N], tout[N], timer{};
 
vector<int> stck;
vector<int> cmp;
 
int mx_cmp {};
 
void dfs(int v, int prev = -1) {
    timer++;
    tin[v] = tout[v] = timer;
    used[v] = true;
    for (pair<int, int> const& cur : g[v]) {
        int u = cur.first;
        int e = cur.second;
        if (u == prev)
            continue;
        if (!used[u]) {
            stck.push_back(e);
            dfs(u, v);
            if (tout[u] >= tin[v]) {
                mx_cmp++;
                while (e != stck.back()) {
                    cmp[stck.back()] = mx_cmp;
                    stck.pop_back();
                }
                cmp[stck.back()] = mx_cmp;
                stck.pop_back();
            }
            if (tout[u] < tout[v])
                tout[v] = tout[u];
        } else {
            if (tin[u] < tin[v])
                stck.push_back(e);
            if (tout[v] > tin[u])
                tout[v] = tin[u];
        }
    }
}
 
void solve() {
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        timer = 0;
        dfs(i);
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
    assert(n >= 0 && n < (int)N);
    assert(m >= 0 && m < (int)M);
    cmp.resize(m);
 
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        assert(x >= 1 && x <= n);
        assert(y >= 1 && y <= n);
        assert(!was.count(make_pair(min(x, y), max(x, y))));
        was.insert({min(x, y), max(x, y)});
        x--; y--;
        g[x].push_back({y, i});
        g[y].push_back({x, i});
    }
 
    solve();
 
    cout << mx_cmp << endl;
 
    for (int i = 0; i < m; i++) {
        assert(cmp[i] > 0);
        cout << cmp[i] << " ";
    }
    return 0;
}
