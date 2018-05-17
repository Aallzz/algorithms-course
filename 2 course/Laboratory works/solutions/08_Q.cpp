#include <bits/stdc++.h>
 
using namespace std;
 
#define taskanme "truth"
#define taski taskanme".in"
#define tasko taskanme".out"
 
constexpr size_t N {1333};
constexpr size_t M {14444};
 
struct edge {
    int to;
    size_t id;
    bool tp;
};
 
vector<edge> g[N];
int cmp[N];
bool type[N];
size_t n, m;
 
bool dfs(int v, int cur_cmp, bool t, size_t cnt) {
    if (cmp[v] != 0) {
        return t == type[v];
    }
    cmp[v] = cur_cmp;
    type[v] = t;
    for (auto const& e : g[v]) {
        if (e.id < cnt && !dfs(e.to, cur_cmp, e.tp ^ t, cnt))
            return false;
    }
    return true;
}
 
bool consistent(size_t n, size_t cnt) {
    fill_n(cmp, n, 0);
    size_t cur_cmp = 0;
    for (size_t i = 0; i < n; i++) {
        if (cmp[i]) continue;
        if (!dfs(i, ++cur_cmp, false, cnt)) {
                return false;
            }
    }
    return true;
}
 
int main() {
 
#ifdef Alex_PKZDL
    ifstream cin(input_file);
    ofstream cout(output_file);
#else
    ifstream cin(taski);
    ofstream cout(tasko);
#endif
 
    cin >> n >> m;
    for (size_t i = 0; i < m; ++i) {
        int x, y; char c; cin >> x >> y >> c; x--; y--;
        g[x].push_back({y, i, c == 'L'});
        g[y].push_back({x, i, c == 'L'});
    }
 
    int l = 1, r = m+1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (consistent(n, mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
 
    cout << l << endl;
    return 0;
}
