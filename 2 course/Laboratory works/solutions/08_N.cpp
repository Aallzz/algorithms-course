#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "avia"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {1333};
constexpr long long inf {(long long)1e16 + 10};
 
long long d[N][N];
int n;
bool used[N];
vector<int> sorted;
 
bool dfs(int v, int value) {
    used[v] = true;
    for (int j = 0; j < n; ++j) {
        if (used[j]) continue;
        if (v == j) continue;
        if (d[v][j] > value) continue;
        dfs(j, value);
    }
    sorted.push_back(v);
    return true;
}
 
bool ddfs(int v, int value, int cmp) {
    used[v] = true;
    for (int j = 0; j < n; ++j) {
        if (used[j]) continue;
        if (v == j) continue;
        if (d[j][v] > value) continue;
        ddfs(j, value, cmp);
    }
    return true;
}
 
int check(int value) {
    fill_n(used, n, false);
    for (int i = 0; i < n; ++i) {
        !used[i] && dfs(i, value);
    }
    fill_n(used, n, false);
    reverse(sorted.begin(), sorted.end());
    int cmp = 0;
    for (int i = 0; i < n; ++i) {
        !used[sorted[i]] && ddfs(sorted[i], value, ++cmp);
    }
    sorted.clear();
    return cmp;
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
 
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> d[i][j];
        }
    }
 
    int l = -1, r = (int)1e9 + 10;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (check(mid) > 1) {
            l = mid;
        } else {
            r = mid;
        }
    }
 
    cout << r << endl;
    return 0;
}
