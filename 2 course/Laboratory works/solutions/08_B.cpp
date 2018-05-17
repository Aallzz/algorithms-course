#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "cond"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {(size_t)2e4 + 10};
 
vector<vector<int>> g;
vector<vector<int>> rg;
vector<int> sorted;
size_t n, m;
bool used[N];
int color[N];
 
void dfs(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (used[to]) continue;
        dfs(to);
    }
    sorted.push_back(v);
}
 
void color_dfs(int v, int cur_color) {
    color[v] = cur_color;
    for (int to : rg[v]) {
        if (!color[to]) {
            color_dfs(to, cur_color);
        }
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
    g.resize(n);
    rg.resize(n);
    for (size_t i = 0; i != m; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        g[x].push_back(y);
        rg[y].push_back(x);
    }
 
    for (size_t i = 0; i != n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
 
    reverse(sorted.begin(), sorted.end());
 
    int cur_color = 0;
    for (int v : sorted) {
        if (!color[v]) {
            color_dfs(v, ++cur_color);
        }
    }
 
    cout << cur_color << endl;
    for (size_t i = 0; i != n; ++i) {
        cout << color[i] << " ";
    }
    cout << endl;
 
    return 0;
}
