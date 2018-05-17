#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = (int)127 + 10;
constexpr int M = (int)5e6 + 10;
constexpr int LG = 10;
constexpr long long mod = (long long)1e9 + 7;
 
struct rectangle {
    int a, b, aa, bb;
 
    rectangle() {};
    rectangle(int a, int b, int aa, int bb) : a(a), b(b), aa(aa), bb(bb) {};
 
    friend istream& operator >> (istream& fin, rectangle& r) {
        fin >> r.a >> r.b >> r.aa >> r.bb;
        if (r.a > r.aa) swap(r.a, r.aa);
        if (r.b > r.bb) swap(r.b, r.bb);
        return fin;
    }
 
    friend rectangle unite(rectangle const& r1, rectangle const& r2) {
        return rectangle(max(r1.a, r2.a), max(r1.b, r2.b), min(r1.aa, r2.aa), min(r1.bb, r2.bb));
    }
 
    long long square() {
        int dx = aa - a;
        int dy = bb - b;
        if (dx < 0) return 0;
        if (dy < 0) return 0;
        return 1LL * dx * dy;
    }
 
};
 
rectangle st[LG][LG][N][N];
int n, m;
int lg[N], v[M << 2];
 
int main() {
    ios_base::sync_with_stdio(false);
 
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        ifstream cin("pail.in");
        ofstream cout("pail.out");
    #endif
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> st[0][0][i][j];
 
 
    for (int i = 0; i < n; ++i)
        for (int lg = 1; lg < LG; ++lg)
            for (int j = 0; j + (1 << (lg - 1)) < m; ++j)
                st[0][lg][i][j] = unite(st[0][lg - 1][i][j], st[0][lg - 1][i][j + (1 << (lg - 1))]);
 
    for (int lg_i = 1; lg_i < LG; ++lg_i)
        for (int i = 0; i + (1 << (lg_i - 1)) < n; ++i)
            for (int lg_j = 0; lg_j < LG; ++lg_j)
                for (int j = 0; j + (1 << lg_j) - 1 < m; ++j)
                    st[lg_i][lg_j][i][j] = unite(st[lg_i - 1][lg_j][i][j], st[lg_i - 1][lg_j][i + (1 << (lg_i - 1))][j]);
 
    lg[1] = 0;
    for (int i = 2; i < max(n, m) + 2; ++i) lg[i] = lg[i >> 1] + 1;
 
    int q; cin >> q;
    int A, B; cin >> A >> B >> v[0];
    for (int i = 1; i < (M << 2); ++i)
        v[i] = (int)((1LL * A * v[i - 1] + B) % mod);
 
    long long ans = 0LL;
    for (int i = 1; i <= q; ++i) {
        int x = v[(i << 2) - 3] % n;
        int y = v[(i << 2) - 2] % m;
        int xx = v[(i << 2) - 1] % n;
        int yy = v[(i << 2)] % m;
        if (x > xx) swap(x, xx);
        if (y > yy) swap(y, yy);
 
        int lg_x = lg[xx - x + 1];
        int lg_y = lg[yy - y + 1];
 
        rectangle res(-1111111, -1111111, 1111111, 1111111);
        res = unite(res, st[lg_x][lg_y][x][y]);
        res = unite(res, st[lg_x][lg_y][xx - (1 << lg_x) + 1][y]);
        res = unite(res, st[lg_x][lg_y][x][yy - (1 << lg_y) + 1]);
        res = unite(res, st[lg_x][lg_y][xx - (1 << lg_x) + 1][yy - (1 << lg_y) + 1]);
 
        (ans += res.square()) %= mod;
    }
 
    cout << ans << endl;
    return 0;
}
