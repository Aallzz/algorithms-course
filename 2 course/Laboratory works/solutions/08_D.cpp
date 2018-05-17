#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "game"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {(size_t)1e5 + 10};
constexpr int inf {(int)1e9 + 10};
 
vector<vector<int>> g;
size_t n, m;
int s;
bool used[N];
bool ans[N];
 
bool dfs(int v) {
    if (used[v])
        return ans[v];
 
    used[v] = true;
 
    if (g[v].size() == 0)
        return ans[v] = false;
 
    bool cur = true;
    for (int to : g[v]) {
        cur &= dfs(to);
    }
 
    return ans[v] = !cur;
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
 
    cin >> n >> m >> s; s--;
    g.resize(n);
    for (size_t i = 0; i != m; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        g[x].push_back(y);
    }
 
    cout << (dfs(s) ? "First player wins" : "Second player wins") << endl;
    return 0;
}
