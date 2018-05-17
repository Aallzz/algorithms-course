nclude <bits/stdc++.h>
 
using namespace std;
 
constexpr size_t N {2333};
constexpr long long inf {(long long)9e18 + 10};
 
struct edge {
    int a, b;
    long long w;
};
 
vector<edge> e;
vector<int> g[N];
 
int n, m, s;
long long d[N];
long long dd[N];
bool used[N];
 
 
void dfs(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (used[to]) continue;
        dfs(to);
    }
}
int main() {
 
#ifdef Alex_PKZDL
    ifstream cin(input_file);
    ofstream cout(output_file);
#endif
 
//    ofstream cout(input_file);
 
//    cout << 100 << " " << 99 * 2 << " " << 1 << endl;
//    for (int i = 0; i < 99 * 2; ++i) {
//        cout << i << " " << i + 1 << " " << 1 << endl;
//        cout << i << " " << i << " " << -1000000000000000 << endl;
//    }
    cin >> n >> m >> s; --s;
    for (int i = 0; i < m; ++i) {
        int x, y; long long w; cin >> x >> y >> w; --x; --y;
        e.push_back({x, y, w});
        g[x].push_back(y);
    }
 
    fill_n(d, n, inf + (long long)1e17);
    d[s] = 0ll;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (d[e[j].a] < inf && d[e[j].b] > d[e[j].a] + e[j].w) {
                d[e[j].b] = max(-inf, d[e[j].a] + e[j].w);
            }
        }
    }
    memcpy(dd, d, n * sizeof(long long));
        for (int j = 0; j < m; ++j) {
            if (dd[e[j].a] < inf && dd[e[j].b] > dd[e[j].a] + e[j].w) {
                dd[e[j].b] = dd[e[j].a] + e[j].w;
            }
        }
 
    for (int i = 0; i < n; ++i) {
        if (d[i] != dd[i]) {
            dfs(i);
        }
    }
 
    for (int i = 0; i < n; ++i) {
        if (d[i] >= inf) cout << "*" << endl;
        else if (d[i] == dd[i] && !used[i]) cout << d[i] << endl;
        else cout << "-" << endl;
    }
    return 0;
}
