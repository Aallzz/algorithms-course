#include <bits/stdc++.h>
 
using namespace std;
 
#define STD_INPUT_OUTPUT
 
#define taskname ""
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = (int)1e5 + 10;
 
vector<int> g[N];
int n, f[N], p[N];
long long hs[N];
 
void dfs(int v, int prev) {
    for (int i = 0; i < (int)g[v].size(); ++i) {
        int to = g[v][i];
        if (to == prev) continue;
        f[to] = f[v] + 1;
        p[to] = v;
        dfs(to, v);
    }
}
 
void ddfs(int v, int prev) {
    hs[v] = 123;
    long long hsh1 = 0, hsh2 = 0;
    for (int i = 0; i < (int)g[v].size(); ++i) {
        int to = g[v][i];
        if (to == prev) continue;
        ddfs(to, v);
        long long son_hash = hs[to];
        hsh1 += son_hash;
        hsh2 ^= son_hash;
    }
    hs[v] += hsh1 + hsh2;
}
 
int main() {
    ios_base::sync_with_stdio(false);
 
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        #ifndef STD_INPUT_OUTPUT
            ifstream cin(taski);
            ofstream cout(tasko);
        #endif // STD_INPUT_OUTPUT
    #endif // Alex_PKZDL
 
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
 
    for (int i = 0; i < n; ++i) f[i] = 0;
    dfs(0, 0);
    int v = 0;
    for (int i = 0; i < n; ++i) {
        if (f[v] < f[i]) v = i;
    }
    for (int i = 0; i < n; ++i) f[i] = 0;
    dfs(v, v);
    for (int i = 0; i < n; ++i) {
        if (f[v] < f[i]) v = i;
    }
 
    if (f[v] % 2 != 0) {
        cout << "NO" << endl;
        return 0;
    }
 
    int len = f[v];
    for (int i = 0; i < len / 2; ++i) v = p[v];
 
    if (g[v].size() != 2) {
        cout << "NO" << endl;
        return 0;
    }
 
    ddfs(v, v);
 
    int to1 = g[v][0];
    int to2 = g[v][1];
 
    if (hs[to1] != hs[to2]) {
        cout << "NO" << endl;
        return 0;
    }
 
    cout << "YES" << endl;
    return 0;
}
