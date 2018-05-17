nclude <bits/stdc++.h>
 
using namespace std;
 
constexpr long long inf {(long long)1e16 + 10};
constexpr size_t N {14444};
 
struct edge {
    int x, y;
    long long w;
};
 
vector<edge> e;
int n, m;
int parent[N], rang[N];
 
void make_sets(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rang[i] = 0;
    }
}
 
int find_set(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find_set(parent[v]);
}
 
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rang[a] < rang[b]) swap(a, b);
        parent[b] = a;
        rang[a] = (rang[a] == rang[b]);
    }
}
 
 
long long get_w_start_from(size_t pos) {
    edge lst {};
    make_sets(n);
    for (size_t i = pos; i < e.size(); ++i) {
        edge cur_e = e[i];
        if (find_set(cur_e.x) == find_set(cur_e.y)) continue;
        union_sets(cur_e.x, cur_e.y);
        lst = cur_e;
    }
    int c = find_set(0);
    for (int i = 0; i < n; ++i) {
        if (c != find_set(i)) return inf;
    }
    return lst.w - e[pos].w;
}
 
int main() {
 
#ifdef Alex_PKZDL
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#endif
 
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        int w; cin >> w;
        e.push_back({x, y, w});
    }
 
    sort(e.begin(), e.end(), [](edge& e1, edge&e2) {
       return e1.w < e2.w;
    });
 
    long long res = inf;
    for (size_t i = 0; i < e.size(); ++i) {
        res = min(res, get_w_start_from(i));
    }
 
    if (res == inf) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << res;
    }
    return 0;
}
