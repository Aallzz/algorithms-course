nclude <bits/stdc++.h>
 
using namespace std;
 
constexpr size_t N {24444};
 
struct edge {
    int a,b, w;
};
 
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
 
vector<edge> e;
int n, m;
 
int main() {
 
#ifdef Alex_PKZDL
    ifstream cin(input_file);
    ofstream cout(output_file);
#endif
 
    cin >> n >> m;
    make_sets(n);
    for (int i = 0; i < m; ++i) {
        int x, y, w; cin >> x >> y >> w; --x; --y;
        e.push_back({x, y, w});
    }
    sort(e.begin(), e.end(), [](edge e1, edge e2) {
        return e1.w < e2.w;
    });
 
    long long ans = 0ll;
    for (edge cur : e) {
        if (find_set(cur.a) == find_set(cur.b)) continue;
        union_sets(cur.a, cur.b);
        ans += cur.w;
    }
 
    cout << ans << endl;
    return 0;
}
