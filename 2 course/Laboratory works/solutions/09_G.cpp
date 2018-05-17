nclude <bits/stdc++.h>
 
using namespace std;
 
constexpr size_t N {5333};
constexpr double inf {1e17 + 10};
constexpr double eps {1e-8};
 
pair<int, int> p[N];
double d[N];
bool used[N];
int n;
 
double dist(pair<int, int> const& p1, pair<int, int> const& p2) {
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return sqrt(dx * dx + dy * dy);
}
 
int main() {
 
#ifdef Alex_PKZDL
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].first >> p[i].second;
    }
    fill_n(d, n, inf);
    fill_n(used, n, false);
    d[0] = 0ll;
 
    double ans = 0.0;
 
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || d[v] > d[j])) {
                v = j;
            }
        }
        if (d[v] == inf) {
            break;
        }
        used[v] = true;
        ans += d[v];
        for (int j = 0; j < n; ++j) {
            double cur_d = dist(p[v], p[j]);
            d[j] = min(d[j], cur_d);
        }
    }
    cout << setprecision(10) << fixed;
    cout << ans << endl;
    return 0;
}
