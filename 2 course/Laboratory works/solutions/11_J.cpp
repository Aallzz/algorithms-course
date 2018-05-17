#include <bits/stdc++.h>
      
using namespace std;
 
#define std_input_output
      
#ifndef std_input_output
    #define taskname ""
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr size_t N {322};
 
int n;
vector<int> c[N];
int matching1[N];
bool used[N];
 
bool dfs(int v, int weight) {
    if (used[v]) return false;
    used[v] = true;
    for (int to = 0; to < n; ++to) {
        if (c[v][to] < weight) continue;
        if (matching1[to] == -1 || dfs(matching1[to], weight)) {
            matching1[to] = v;
            return true;
        }
    }
    return false;
}
 
bool full_mathcing(int weight) {
    fill_n(matching1, n, -1);
    for (int i = 0; i < n; ++i) {
        fill_n(used, n, 0);
        dfs(i, weight);
    }
 
    for (int i = 0; i < n; ++i) 
        if (matching1[i] == -1) return false;
     
    return true;
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
        for (int j = 0; j < n; ++j) {
            int p; cin >> p;
            c[i].push_back(p);
        }
    }
 
    int l = 0, r = 1666666;
     
    while (r - l > 1) {
        int mid = (l + r) / 2;
        
        if (full_mathcing(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
     
    if (full_mathcing(r)) cout << r << endl;
    else cout << l << endl;
    return 0;
} 
