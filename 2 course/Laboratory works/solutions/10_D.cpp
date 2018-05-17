#include <bits/stdc++.h>

using namespace std;

//#define std_input_output

#ifndef std_input_output
   #define taskname "birthday"
   #define taski taskname".in"
   #define tasko taskname".out"
#endif

constexpr size_t N {200};

int n, m;
int g[N][N];
int used1[N], used2[N];
int matching1[N], matching2[N];
int ans1[N], ans2[N];
int cnt1, cnt2;

bool matching_dfs(int v) {
   if (used1[v]) return false;
   used1[v] = true;
   for (int to = 0; to < m; ++to) {
       if (g[v][to] != 0) continue;
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
   for (int to = 0; to < m; ++to) {
       if (g[v][to] != 0) continue;
       if (matching1[v] == to) continue;
       if (used2[to]) continue;
       used2[to] = true;
       if (matching2[to] != -1)
           partition_dfs(matching2[to]);
   }
}

void read_input() {
   cin >> n >> m;
   for (int i = 0; i < n; ++i) {
       int x;
       fill_n(g[i], m, 0);
       while (cin >> x) {
           if (x == 0) break;
           g[i][x - 1] = 1;
       }
   }
}

void solve() {
   fill_n(matching1, n, -1);
   fill_n(matching2, m, -1);
   fill_n(used1, n, false);
   for (int i = 0; i < n; ++i) {
       matching_dfs(i);
       fill_n(used1, n, false);
   }

   for(int i = 0; i < n; ++i) {
       if (matching1[i] != -1) continue;
       partition_dfs(i);
   }
}

void write_output() {
   cnt1 = n, cnt2 = m;
   for (int i = 0; i < n; ++i) {
       if (used1[i]) continue;
       ans1[i] = 1;
       cnt1--;
   }
   for (int i = 0; i < m; ++i) {
       if (!used2[i]) continue;
       ans2[i] = 1;
       cnt2--;
   }
   cout << cnt1 + cnt2 << endl;
   cout << cnt1 << " " << cnt2 << endl;

   for (int i = 0; i < n; ++i) {
       if (ans1[i]) continue;
       cout << i + 1 << " ";
   }
   cout << endl;
   for (int i = 0; i < m; ++i) {
       if (ans2[i]) continue;
       cout << i + 1 << " ";
   }
   cout << endl;
   cout << endl;
}

void clear_data() {
   for (int i = 0; i < n; ++i) ans1[i] = 0;
   for (int i = 0; i < m; ++i) ans2[i] = 0;
   fill_n(used2, m, false);
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

   int tests; cin >> tests;
   while (tests--) {
       read_input();
       solve();
       write_output();
       clear_data();
   }
   return 0;
}
