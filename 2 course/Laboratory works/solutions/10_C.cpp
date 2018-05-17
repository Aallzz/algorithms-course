#include <bits/stdc++.h>
 
using namespace std;
 
#define std_input_output
 
//#ifndef std_input_output
    #define taskname "vertexcover"
    #define taski taskname".in"
    #define tasko taskname".out"
//#endif
 
constexpr size_t N {4333};
 
int n, m;
vector<int> g[N];
int matching2[N];
int matching1[N];
bool used2[N];
bool used1[N];
 
void dfs(int v) {
    if (used1[v]) return ;
    used1[v] = true;
    for (int to : g[v]) {
        if (matching1[v] == to) continue;
        if (used2[to]) continue;
        used2[to] = true;
        if (matching2[to] != -1) {
            dfs(matching2[to]);
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
 
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int x; cin >> x; x--;
            g[i].push_back(x);
        }
    }
 
    fill_n(matching2, m, -1);
 
    for (int i = 0; i < n; ++i) {
        int x; cin >> x; x--;
        if (x != -1)
            matching2[x] = i;
        matching1[i] = x;
    }
 
    for (int i = 0; i < n; ++i) {
        if (matching1[i] != -1) continue;
        dfs(i);
    }
 
    vector<int> ans1;
    vector<int> ans2;
    for (int i = 0; i < n; ++i) {
        if (used1[i]) continue;
        ans1.push_back(i + 1);
    }
    for (int i = 0; i < m; ++i) {
        if (!used2[i]) continue;
        ans2.push_back(i + 1);
    }
 
    cout << ans1.size() + ans2.size() << endl;
    cout << ans1.size() << " ";
    for (int x : ans1) cout << x << " ";
    cout << endl << ans2.size() << " ";
    for (int x : ans2) cout << x << " ";
    cout << endl;
    return 0;
}
