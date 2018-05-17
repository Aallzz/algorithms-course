#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "cnf"
#define taski taskname".in"
#define tasko taskname".out"
 
int n, m;
vector < vector<int> > g, gt;
vector<bool> used;
vector<int> order, comp;
 
void normalize(int& a) {
    if (a > 0) {
        a--;
        a *= 2;
    } else {
        a = -a;
        a *= 2;
        a--;
    }
}
 
int negate(int a) {
    if (a % 2 == 0) {
        return a + 1;
    } else {
        return a - 1;
    }
}
void dfs1 (int v) {
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs1 (to);
    }
    order.push_back (v);
}
 
void dfs2 (int v, int cl) {
    comp[v] = cl;
    for (size_t i=0; i<gt[v].size(); ++i) {
        int to = gt[v][i];
        if (comp[to] == -1)
            dfs2 (to, cl);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
 
#ifdef Alex_PKZDL
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#else
    freopen(taski, "r", stdin);
    freopen(tasko, "w", stdout);
#endif
 
    cin >> n >> m;
    g.resize(n + n);
    gt.resize(n + n);
    for (int i = 0; i < m; ++i) {
        int x, y, z; cin >> x >> y >> z;
        normalize(x);
        normalize(y);
        normalize(z);
 
        using ::negate;
        g[negate(x)].push_back(y);
        g[negate(y)].push_back(x);
 
        g[negate(x)].push_back(z);
        g[negate(z)].push_back(x);
 
        g[negate(z)].push_back(y);
        g[negate(y)].push_back(z);
 
        gt[y].push_back(negate(x));
        gt[x].push_back(negate(y));
 
        gt[z].push_back(negate(x));
        gt[x].push_back(negate(z));
 
        gt[y].push_back(negate(z));
        gt[z].push_back(negate(y));
 
    }
 
    n += n;
 
    used.assign (n, false);
    for (int i=0; i<n; ++i)
        if (!used[i])
            dfs1 (i);
 
    comp.assign (n, -1);
    for (int i=0, j=0; i<n; ++i) {
        int v = order[n-i-1];
        if (comp[v] == -1)
            dfs2 (v, j++);
    }
 
    for (int i=0; i<n; ++i)
        if (comp[i] == comp[i^1]) {
            puts ("NO");
            return 0;
        }
 
    cout << "YES" << endl;
    for (int i=0; i<n; i += 2) {
        int ans = comp[i] > comp[i^1] ? i : i^1;
        if (ans % 2 == 0) {
            ans /= 2;
            ans++;
        } else {
            ans++;
            ans /= -2;
        }
        cout << ans << " ";
    }
 
    return 0;
}
