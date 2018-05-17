#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "treedp"
#define taski taskname".in"
#define tasko taskname".out"
 
typedef long long ll;
 
const int N = (int)3e5 + 10;
 
ll f[N], sz[N], up, n;
vector<pair<int, int> > g[N];
vector<ll> ans;
 
void dfs1(int v, int prev = 0)
{
    f[v] = 0;
    sz[v] = 1;
    for (int i = 0; i < (int)g[v].size(); ++i){
        int to = g[v][i].first;
        if (to == prev) continue;
        dfs1(to, v);
        sz[v] += sz[to];
        f[v] += sz[to] + f[to];
    }
}
 
void dfs2(int v, int prev = 0){
 
    up += f[v];
 
    for (int i = 0; i < (int)g[v].size(); ++i){
        int to = g[v][i].first;
        int idx = g[v][i].second;
        if (to == prev) continue;
        ans[idx] = sz[to] * (n - sz[to]) + sz[to] * (up - sz[to] - f[to]) + (n - sz[to]) * f[to];
        up += (n - sz[to]) - f[to] - sz[to];
        dfs2(to, v);
        up -= (n - sz[to]) - f[to] - sz[to];
    }
 
    up -= f[v];
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif
 
    cin >> n;
    for (int i = 0; i < n - 1; ++i){
        ans.push_back(0LL);
        int x, y; cin >> x >> y; x--; y--;
        g[x].push_back(make_pair(y, i));
        g[y].push_back(make_pair(x, i));
    }
 
    dfs1(0);
    dfs2(0);
 
    for (int i = 0; i < n - 1; ++i) cout << ans[i] << endl;
    return 0;
}
