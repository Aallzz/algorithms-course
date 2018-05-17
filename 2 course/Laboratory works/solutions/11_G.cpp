#include <bits/stdc++.h>
  
using namespace std;
 
#define std_input_output
  
#ifndef std_input_output
    #define taskname ""
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr size_t N {322};
constexpr int inf {1999999999};
 
int d[N][N], u[N], v[N], p[N], way[N];
int n;
 
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
 
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> d[i][j];
     
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int jj = 0;
        vector<int> minv(n + 1, inf);
        vector<char> used(n + 1, false);
        do {
            used[jj] = true;
            int ii {p[jj]};
            int dd {inf};
            int jjj {-1};
            for (int j = 1; j <= n; ++j) {
                if (used[j]) continue;
                int cur = d[ii][j] - u[ii] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = jj;
                }
                if (minv[j] < dd) {
                    dd = minv[j];
                    jjj = j;
                }
            }
            for (int j = 0; j <= n; ++j) {
                if (used[j]) {
                   u[p[j]] += dd;
                   v[j] -= dd;
                } else {
                    minv[j] -= dd;
                }
            }
            jj = jjj;
        } while (p[jj] != 0);
        do {
            int jjj = way[jj];
            p[jj] = p[jjj];
            jj = jjj;
        } while (jj);
    }
 
    long long ans = 0ll;
    vector<pair<int, int>> vans;
    for (int i = 1; i <= n; ++i) ans += d[p[i]][i], vans.push_back({p[i], i});
    cout << ans << endl;
    for (auto const& cur : vans) cout << cur.first << " " << cur.second << endl;
    return 0;
}
