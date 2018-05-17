#include <bits/stdc++.h>
 
using namespace std;
 
//#define std_input_output
 
#ifndef std_input_output
    #define taskname "paths"
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr size_t N {24444};
 
struct edge {
    int a {}, b {};
    bool real {};
 
    edge(int a, int b, bool real) :
        a{a}, b{b}, real{real}
    {};
};
 
int n, m;
vector<edge> e;
vector<int> g[N];
vector<int> path;
 
map<pair<int, int>, int> a;
multiset<pair<int, int>> fake;
 
void add_fake_edges() {
    int lst = -1;
    for (int i = 0; i < n; ++i) {
        if (g[i].size() & 1) {
            if (lst != -1) {
                g[i].push_back((int)(int)e.size());
                g[lst].push_back((int)e.size());
                e.emplace_back(i, lst, false);
                fake.insert({i, lst});
                fake.insert({lst, i});
                a[{min(lst, i), max(lst, i)}] += 2;
                lst = -1;
            } else {
                lst = i;
            }
        }
    }
}
 
void get_euler_path() {
    vector<int> st;
    st.push_back(0);
    while (!st.empty()) {
        int v = st.back();
        int to = v;
        while (g[v].size() != 0 && a[{min(to, v), max(to, v)}] < 2) {
            to = e[g[v].back()].a ^ e[g[v].back()].b ^ v;
            g[v].pop_back();
        }
        if (a[{min(to, v), max(to, v)}] < 2) {
            path.push_back(v);
            st.pop_back();
        } else {
            st.push_back(to);
            a[{min(to, v), max(to, v)}] -= 2;
        }
    }
}
int main() {
 
#ifdef HOME
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#else
    #ifndef std_input_output
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif
#endif
 
    ios_base::sync_with_stdio(false);
 
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        g[x].push_back((int)e.size());
        g[y].push_back((int)e.size());
        e.emplace_back(x, y, true);
        a[{min(x, y), max(x, y)}] += 2;
    }
 
    add_fake_edges();
    get_euler_path();
 
    vector<vector<int>> ans;
    int cur = 0;
    ans.push_back(vector<int>());
 
    for (int i = 0; i < (int)path.size() - 1; ++i) {
        ans[cur].push_back(path[i]);
        if (fake.count({path[i], path[i + 1]})) {
            fake.erase({path[i], path[i + 1]});
            fake.erase({path[i + 1], path[i]});
            cur++;
            ans.push_back(vector<int>());
        }
    }
    ans[cur].push_back(path.back());
    int add = 0;
    if (cur != 0) {
        ans[cur].insert(ans[cur].end(), ans[0].begin() + 1, ans[0].end());
        ans[0].clear();
        add = 1;
    }
 
    cout << ans.size() - add << endl;
    for (auto const& v : ans) {
        for (int c : v) {
            cout << c + 1 << " ";
        }
        if (v.size()) cout << endl;
    }
    return 0;
}
