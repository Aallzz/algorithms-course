#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "dfs"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {888};
 
int n, m;
int v[N], a[N][N], pos[N];
 
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
    fill_n(pos, n, -1);
 
    for (int i = 0; i < m; ++i) {
        cin >> v[i]; v[i]--;
    }
 
    for (int i = 0; i < m; ++i) {
        int& prev_pos = pos[v[i]];
        if (prev_pos != -1) {
            for (int j = prev_pos + 1; j < i; ++j) {
                if (v[j] >= v[i - 1]) {
                    a[v[i]][v[j]] = a[v[j]][v[i]] = 1;
                }
            }
        }
        prev_pos = i;
    }
 
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            cnt += a[i][j];
 
    cout << cnt << endl;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (a[i][j])
                cout << i + 1 << " " << j + 1 << endl;
    return 0;
}
