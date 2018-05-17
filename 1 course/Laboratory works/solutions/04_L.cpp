#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "matching"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)1e5 + 10;
const long long inf = (long long)1e16 + 10;
 
int n;
vector<pair<int, long long> > g[N];
long long f[N][2];
 
void dfs(int v, int prev = -1){
    long long sum = 0LL;
 
    if (g[v].size() == 1 && prev != -1) return ;
 
    for (int i = 0; i < (int)g[v].size(); ++i){
        int to = g[v][i].first;
        if (to == prev) continue;
        dfs(to, v);
        sum += max(f[to][0], f[to][1]);
    }
 
    f[v][0] = sum;
    f[v][1] = 0LL;
 
    for (int i = 0; i < (int)g[v].size(); ++i){
        int to = g[v][i].first;
        long long w = g[v][i].second;
        if (to == prev) continue;
        long long curSum = sum - max(f[to][0], f[to][1]);
        curSum += w + f[to][0];
        f[v][1] = max(curSum, f[v][1]);
    }
}
 
int main()
{
    ios_base::sync_with_stdio(false);
 
    #ifndef Alex_PKZDL
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    cin >> n;
    for (int i = 0; i < n - 1; ++i){
        int x, y, w; cin >> x >> y >> w; x--; y--;
        g[x].push_back(make_pair(y, w));
        g[y].push_back(make_pair(x, w));
    }
 
    dfs(0);
 
    cout << max(f[0][0], f[0][1]) << endl;
 
    return 0;
}
