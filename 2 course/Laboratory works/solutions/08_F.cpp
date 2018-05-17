#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "hamiltonian"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {(size_t)1e5 + 10};
constexpr int inf {(int)1e9 + 10};
 
vector<vector<int>> g;
size_t n, m;
 
int cnt[N];
bool used[N];
 
int dfs(int v) {
    if (used[v]) return cnt[v];
    used[v] = true;
 
    if (g[v].size() == 0)
        return cnt[v] = 1;
 
    for (int to : g[v]) {
        cnt[v] = max(cnt[v], dfs(to));
    }
    return ++cnt[v];
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
    for (size_t i = 0; i != m; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        g[x].push_back(y);
    }
 
    for (size_t i = 0; i != n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
 
    for (size_t i = 0; i != n; ++i) {
        if (cnt[i] == (int)n) {
            cout << "YES" << endl;
            return 0;
        }
    }
 
    cout << "NO" << endl;
    return 0;
}
