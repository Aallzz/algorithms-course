#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "components"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {(size_t)1e5 + 10};
constexpr size_t M {(size_t)2e5 + 10};
 
vector<vector<int>> g;
vector<int> cmp;
 
void dfs(int v, int cur_cmp) {
    cmp[v] = cur_cmp;
    for (int to : g[v]) {
        if (cmp[to]) continue;
        dfs(to, cur_cmp);
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
 
    int n, m;
    cin >> n >> m;
 
    g.resize(n);
    cmp.resize(n);
 
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
 
    int current_cmp = 0;
    for (int i = 0; i < n; ++i) {
        if (!cmp[i]) {
            dfs(i, ++current_cmp);
        }
    }
 
    cout << current_cmp << endl;
    for (int i = 0; i < n; ++i) {
        cout << cmp[i] << " ";
    }
    cout << endl;
    return 0;
}
