#include <bits/stdc++.h>
 
using namespace std;
 
constexpr size_t N {333};
const string colors = "WB";
 
//#define std_input_output
 
#ifndef std_input_output
    #define taskname "chess"
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
int n, m;
vector<string> field;
vector<int> g[N];
vector<int> matching1, matching2;
vector<bool> used1, used2;
 
char rev(char color) {
    return color == 'W' ? 'B' : 'W';
}
 
bool tp(int x, int y) {
    return (x + y) & 1;
}
 
bool matching_dfs(int v) {
    if (used1[v]) return false;
    used1[v] = true;
    for (int to : g[v]) {
        if (matching2[to] == -1 || matching_dfs(matching2[to])) {
            matching2[to] = v;
            matching1[v] = to;
            return true;
        }
    }
    return false;
}
 
void partition_dfs(int v) {
    if (used1[v]) return ;
    used1[v] = true;
    for (int to : g[v]) {
        if (matching1[v] == to) continue;
        if (used2[to]) continue;
        used2[to] = true;
        if (matching2[to] != -1)
            partition_dfs(matching2[to]);
    }
}
 
 
void build_graph(char color) {
    for (int i = 0; i < n + m; ++i) g[i].clear();
 
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
           if (tp(i, j) && field[i][j] == color)
               g[i + j].push_back(i - j + (m - 1));
           if (!tp(i, j) && field[i][j] != color)
               g[i + j].push_back(i - j + (m - 1));
        }
    }
}
 
void build_matching() {
    int sz = n + m - 1;
    used1.assign(sz, false);
    matching1.assign(sz, -1);
    matching2.assign(sz, -1);
    for (int i = 0; i < sz; ++i) {
        matching_dfs(i);
        used1.assign(sz, false);
    }
}
 
void build_partition() {
    int sz = n + m - 1;
    used1.assign(sz, false);
    used2.assign(sz, false);
    //for (int i = 0; i < sz; ++i) {
    //    cout << matching1[i] << " " << matching2[i] << endl;
    //}
 
    for (int i = 0; i < sz; ++i) {
        if (matching1[i] != -1) continue;
        partition_dfs(i);
    }
}
 
vector<tuple<int, int, int, char>>  calc_cover(char color) {
    int sz = n + m - 1;
    vector<tuple<int, int, int, char>> ans;
    for (int i = 0; i < sz; ++i) {
        if (used1[i]) continue;
        for (int p1 = 0; p1 < n; ++p1) {
            int p2 = i - p1;
            if (0 > p2 || p2 >=m) continue;
            ans.push_back(std::make_tuple(1, p1, p2, tp(p1, p2) ? rev(color) : color));
            break;
        }
    }
 
    for (int i = 0; i < sz; ++i) {
        if (!used2[i]) continue;
        for (int p1 = 0; p1 < n; ++p1) {
            int p2 = p1 - (i - (m - 1));
            if (0 > p2 || p2 >=m) continue;
            ans.push_back(std::make_tuple(2, p1, p2, tp(p1, p2) ? rev(color) : color));
            break;
        }
    }
 
    return ans;
}
 
vector<tuple<int, int, int, char>> cover_min(vector<tuple<int, int, int, char>> const& v1,
                                             vector<tuple<int, int, int, char>> const& v2) {
    return v1.size() < v2.size() ? v1 : v2;
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
    cin >> n >> m;
    field.resize(n);
    vector<tuple<int, int, int, char>> ans(433);
    for (auto& s : field) cin >> s;
    for (char c : colors) {
        build_graph(c);
        build_matching();
        build_partition();
        ans = cover_min(ans, calc_cover(c));
    }
 
    cout << ans.size() << endl;
    for (auto const& cur : ans) {
        cout << get<0>(cur) << " " << get<1>(cur) + 1 << " " << get<2>(cur) + 1 << " " << get<3>(cur) << endl;
    }
 
    return 0;
}
