#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "bipartite"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {(size_t)1e5 + 10};
constexpr size_t M {(size_t)2e5 + 10};
 
int n, m;
vector<vector<int>> g;
int part[N];
 
bool dfs(int v, int prev = -1, int p = 1) {
    part[v] = p;
    bool res = true;
    for (int to : g[v]) {
        if (part[to]) {
            if (part[to] == p)
                return false;
        } else {
           if (to != prev)
                res &= dfs(to, v, (p == 1 ? 2 : 1));
        }
    }
    return res;
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
        g[x].push_back(y);
        g[y].push_back(x);
    }
 
    bool res = true;
    for (int i = 0; i < n; ++i) {
        if (!part[i]) res &= dfs(i);
    }
 
    cout << (res ? "YES" : "NO") << endl;
    return 0;
}

