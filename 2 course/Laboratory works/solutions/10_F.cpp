#include <bits/stdc++.h>
 
using namespace std;
 
//#define std_input_output
 
#ifndef std_input_output
    #define taskname "king"
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr size_t N {2333};
int n;
vector<int> g[N + N], rg[N + N];
int matching1[N + N], matching2[N + N];
vector<int> ans[N + N];
vector<int> sorted;
bool used[N + N];
int color[N + N];
 
void dfs(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (matching1[v] == to) continue;
        if (used[to]) continue;
        dfs(to);
    }
    sorted.push_back(v);
}
 
void color_dfs(int v, int cur_color) {
    color[v] = cur_color;
    for (int to : rg[v]) {
        if (matching2[v] == to) continue;
        if (!color[to]) {
            color_dfs(to, cur_color);
        }
    }
}
 
int main() {
 
#ifdef HOME
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#else
    #ifndef std_input_output
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif
#endif
 
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int x; cin >> x; x--;
            g[i].push_back(x + n);
            rg[x + n].push_back(i);
        }
    }
 
    fill_n(matching1, n + n, -1);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x; x--;
        matching1[i] = x + n;
        matching2[x + n] = i;
        g[x + n].push_back(i);
        rg[i].push_back(x + n);
 
        ans[i].push_back(x);
    }
 
    for (int i = 0; i != n; ++i) {
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
 
    for (int v = 0; v < n; ++v) {
        for (int to : g[v]) {
            if (color[v] == color[to]) {
                ans[v].push_back(to - n);
            }
        }
    }
 
    for (int i = 0; i < n; ++i) {
        sort(ans[i].begin(), ans[i].end());
        ans[i].resize(unique(ans[i].begin(), ans[i].end()) - ans[i].begin());
        cout << ans[i].size() << " ";
        for (int v : ans[i]) {
            cout << v + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
