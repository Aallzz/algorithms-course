#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "fun"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr long long linf = (long long)1e18 + 10;
constexpr int inf = (int)1e9 + 10;
constexpr int N = (int)2e5 + 10;
constexpr int M = (int)1e6 + 10;
 
struct query_type {
    int l, r, idx;
    int block;
    long long ans;
} query[N];
 
long long a[N];
int n, m;
int block;
 
long long res = 0LL;
int cnt[M];
 
int left_bound, right_bound;
long long cur;
 
 
bool cmp1(query_type const& x, query_type const& y) {
    return x.block == y.block ? x.r < y.r : x.l < y.l;
}
 
bool cmp2(query_type const& x, query_type const& y) {
    return x.idx < y.idx;
}
 
int main() {
 
    #ifdef Alex_PKZDL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
//        ifstream cin("input.txt");
//        ofstream cout("output.txt");
    #else
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
//        ifstream cin(taski);
//        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
//    cin >> n >> m;
    scanf("%d%d", &n, &m);
//    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) scanf("%I64d", a + i);
 
    block = min((int)(1.54 * sqrt(m) + 1), m);
    for (int i = 0; i < m; ++i) {
        int x, y;
//        cin >> x >> y;
        scanf("%d%d", &x, &y);
        x--; y--;
        query[i] = {x, y, i, x / block, -1};
    }
    sort(query, query + m, cmp1);
 
    int l, r;
    l = 0;
    r = -1;
 
    for (int i = 0; i < m; ++i) {
        left_bound = query[i].l;
        right_bound = query[i].r;
        while (r < right_bound) {
            r++;
            cur = a[r];
            res += ((cnt[cur] << 1) + 1) * cur;
            cnt[cur]++;
        }
        while (l > left_bound) {
            l--;
            cur = a[l];
            res += ((cnt[cur] << 1) + 1) * cur;
            cnt[cur]++;
        }
        while (l < left_bound) {
            cur = a[l];
            res -= ((cnt[cur] << 1) - 1) * cur;
            cnt[cur]--;
            l++;
        }
        while (r > right_bound) {
            cur = a[r];
            res -= ((cnt[cur] << 1) - 1) * cur;
            cnt[cur]--;
            r--;
        }
        query[i].ans = res;
    }
 
    sort(query, query + m, cmp2);
 
    for (int i = 0; i < m; ++i) {
        printf("%I64d\n", query[i].ans);
//        cout << query[i].ans << "\n";
    }
    return 0;
}
