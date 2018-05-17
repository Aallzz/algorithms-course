#include <bits/stdc++.h>

using namespace std;

#define taskname "points"
#define taski taskname".in"
#define tasko taskname".out"

constexpr size_t N {(size_t)2e4 + 10};
constexpr size_t M {(size_t)2e5 + 10};

int n, m;
vector<vector<int>> g;
vector<int> points;

int up[N], h[N];
bool used[N];

void dfs(int v, int prev = -1) {
    used[v] = true;
    bool is_point = false;
    int children = 0;
    up[v] = h[v] = (prev == -1 ? 0 : h[prev] + 1);
    for (int to : g[v]) {
        if (to == prev) continue;
        if (used[to]) {
            up[v] = min(up[v], h[to]);
            continue;
        }
        dfs(to, v);
        up[v] = min(up[v], h[to]);
        if (h[to] > h[v]) {
            up[v] = min(up[v], up[to]);
            children++;
            is_point |= (up[to] >= h[v] && prev != -1);
        }
    }
    is_point |= (prev == - 1 && children > 1);
    if (is_point)
        points.push_back(v);
}

int main() {
    ios_base::sync_with_stdio(false);

#ifdef Alex_PKZDL
    ifstream cin(input_file);
    ofstream cout(output_file);
#else
    ifstream cin(taski);
    ofstream cout(tasko);
#endif

    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i != m; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (int i = 0; i != n; ++i) {
        sort(g[i].begin(), g[i].end());
        g[i].resize(unique(g[i].begin(), g[i].end()) - g[i].begin());
    }

    for (int i = 0; i != n; ++i) {
        if (used[i]) continue;
        dfs(i);
    }

    sort(points.begin(), points.end());
    cout << points.size() << endl;
    for (int const& x : points) cout << x + 1 << " ";
    cout << endl;
    return 0;
}

