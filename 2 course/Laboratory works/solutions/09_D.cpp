nclude <bits/stdc++.h>
 
using namespace std;
 
constexpr size_t N {34444};
constexpr size_t M {455555};
constexpr long long inf {(long long)1e16 + 10};
 
int n, m;
vector<pair<int, int>> g[N];
priority_queue<pair<int, int>> q;
long long d[N];
 
int main() {
 
#ifdef Alex_PKZDL
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        --x; --y;
        g[x].push_back({y, w});
        g[y].push_back({x, w});
    }
    for (int i = 0; i < n; ++i) d[i] = inf;
    d[0] = 0;
    q.push({0, 0});
    while (!q.empty()) {
        int cur_d = -q.top().first;
        int cur_v = q.top().second;
        q.pop();
        if (cur_d > d[cur_v]) continue;
        for (auto e : g[cur_v]) {
            int to = e.first;
            int w = e.second;
            if (w + cur_d < d[to]) {
                q.push({-(cur_d + w), to});
                d[to] = w + cur_d;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << d[i] << " ";
    }
    return 0;
}
