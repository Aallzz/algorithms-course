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
int p[N];
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
 
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x, y; long long w; cin >> w; x = i, y = j;
            e.push_back({x, y, w});
            g[x].push_back(y);
        }
    }
 
    fill_n(d, n, inf + (long long)1e17);
    fill_n(p, n, -1);
    d[s] = 0ll;
    m = e.size();
    int lst = -1;
    for (int i = 0; i < n; ++i) {
        lst = -1;
        for (int j = 0; j < m; ++j) {
            if (d[e[j].a] < inf && d[e[j].b] > d[e[j].a] + e[j].w) {
                d[e[j].b] = max(-inf, d[e[j].a] + e[j].w);
                p[e[j].b] = j;
                lst = e[j].b;
            }
        }
    }
 
    if (lst == -1) {
        cout << "NO" << endl;
        return 0;
    }
 
    int y = lst;
    for (int i = 0; i < n; ++i)
        y = e[p[y]].a;
 
    vector<int> way;
    for (int v = y;; v = e[p[v]].a) {
        way.push_back (v);
        if (v == y && way.size() > 1)
            break;
    }
 
    reverse (way.begin(), way.end());
 
    cout << "YES" << endl;
    cout << way.size() << endl;
    for (int v : way) {
        cout << v + 1 << " ";
    }
    cout << endl;
    return 0;
}
