nclude <bits/stdc++.h>
 
using namespace std;
 
vector<vector<int>> g;
int n, m;
vector<int> d;
queue<int> q;
 
int main() {
 
#ifdef Alex_PKZDL
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#endif
 
    cin >> n >> m;
    g.resize(n, vector<int>());
    d.resize(n, -1);
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y; --x; --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    d[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (d[to] != -1) continue;
            d[to] = d[v] + 1;
            q.push(to);
        }
    }
    for (int dst : d) cout << dst << " ";
    cout << endl;
    return 0;
}
