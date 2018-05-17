#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "topsort"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {(size_t)1e5 + 10};
 
vector<int> g[N];
vector<int> ans;
 
size_t n, m;
int used[N];
 
void dfs(int v, int prev = -1) {
    used[v] = 1;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == prev) continue;
        if (used[to] == 2) continue;
        if (used[to] == 1) {
            return ;
        }
        dfs(to, v);
    }
    used[v] = 2;
    ans.push_back(v);
}
 
 
int main() {
    ios_base::sync_with_stdio(false);
 
#ifdef Alex_PKZDL
    ifstream cin(input_file);
    ofstream cout(output_file);
#else
    ifstream cin("topsort.in");
    ofstream cout("topsort.out");
#endif
 
    cin >> n >> m;
    for (size_t i = 0; i < m; ++i) {
        int x, y; cin >> x >> y; --x; --y;
        g[x].push_back(y);
    }
 
    for (size_t i = 0; i < n; ++i) {
        if (!used[i])
            dfs(i);
    }
 
    reverse(ans.begin(), ans.end());
    if (ans.size() != n) {
        cout << -1 << endl;
    } else {
        for (auto i : ans) {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
