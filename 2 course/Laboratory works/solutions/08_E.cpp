#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "cycle"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {(size_t)1e5 + 10};
constexpr int inf {(int)1e9 + 10};
 
vector<vector<int>> g;
size_t n, m;
 
int used[N];
int cycle_start = -1;
vector<int> cycle;
 
int dfs(int v) {
    used[v] = 1;
    cycle.push_back(v);
    for (int to : g[v]) {
        if (used[to] == 1) {
            cycle_start = to;
            return cycle_start;
        }
        if (used[to] == 2) continue;
        if (dfs(to) != -1) {
            return cycle_start;
        }
    }
    used[v] = 2;
    cycle.pop_back();
    return cycle_start;
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
            if (dfs(i) != -1) {
                cout << "YES" << endl;
                vector<int> ans;
                while (cycle.back() != cycle_start) {
                    ans.push_back(cycle.back());
                    cycle.pop_back();
                }
                ans.push_back(cycle.back());
                reverse(ans.begin(), ans.end());
                for (int x : ans) {
                    cout << x + 1 << " ";
                }
                cout << endl;
                return 0;
            }
        }
    }
 
    cout << "NO" << endl;
    return 0;
}
