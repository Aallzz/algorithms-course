#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "lca_rmq"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int LG = 21;
constexpr int N = (int)1e5 + 10;
 
int n, m;
vector<int> g[N];
vector<pair<int, int>> p;
int pos[N];
vector<int> lg;
 
 
vector<pair<int, int>> st[LG];
 
void dfs(int v, int h = 0) {
    pos[v] = p.size();
    p.push_back({h, v});
    for (int to : g[v]) {
        dfs(to, h + 1);
        p.push_back({h, v});
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
#ifdef Alex_PKZDL
    ifstream cin("input.txt");
    ofstream cout("output.txt");
#else
    ifstream cin(taski);
    ofstream cout(tasko);
#endif
 
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int x; cin >> x;
        g[x].push_back(i);
    }
 
    dfs(0);
 
    st[0] = p;
    for (int lg = 1; lg < LG; ++lg) {
        st[lg].resize(p.size());
        for (int i = 0; i + (1 << (lg - 1)) < (int)p.size(); ++i) {
            st[lg][i] = min(st[lg - 1][i], st[lg - 1][i + (1 << (lg - 1))]);
        }
    }
 
    lg.resize(p.size());
    lg[1] = 0;
    for (int i = 2; i < (int)p.size(); ++i) {
        lg[i] = lg[i >> 1] + 1;
    }
 
    int a, b; cin >> a >> b;
    int x, y, z; cin >> x >> y >> z;
 
    unsigned long long res = 0ULL;
 
    int prev_v = 0;
 
    for (int i = 0; i < m; ++i) {
 
        int aa = (a + prev_v) % n;
        int bb = b;
//        int aa, bb; cin >> aa >> bb;
        if (pos[aa] > pos[bb]) swap(aa, bb);
        int pw = lg[pos[bb] - pos[aa] + 1];
 
        auto cur_res = min(st[pw][pos[aa]], st[pw][pos[bb] - (1 << pw) + 1]);
        res += cur_res.second;
        prev_v = cur_res.second;
 
//        cout << cur_res.second << endl;
        a = (int)((1LL * x * a + 1LL * y * b + z) % (long long)n);
        b = (int)((1LL * x * b + 1LL * y * a + z) % (long long)n);
 
    }
 
    cout << res << endl;
    return 0;
}
