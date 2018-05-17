#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)1e6 + 10;
const int mod = (int)1e6 + 3;
 
#define taskname "dsu"
#define taski taskname".in"
#define tasko taskname".out"
 
#ifndef Alex_PKZDL
#define file ifstream cin(taski); ofstream cout(tasko)
//#define file freopen(taski, "r", stdin); freopen(tasko, "w", stdout)
#else
//#define file ifstream cin("input.txt"); ofstream cout("output.txt")
#define file freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#endif
 
struct DSU{
    int parent[N], sz[N], cnt[N];
 
    void makeSets(int n){
        for (int i = 0; i < n; ++i){
            parent[i] = i;
            sz[i] = 1;
            cnt[i] = 0;
        }
    }
 
    pair<int, int> findSetPair(int v){
        if (parent[v] == v) return make_pair(v, cnt[v]);
        pair<int, int> res = findSetPair(parent[v]);
        cnt[v] = (parent[v] == res.first ? 0 : res.second) + cnt[v];
        parent[v] = res.first;
        return make_pair(parent[v], cnt[v]);
    }
 
    int findSet(int v){
        return findSetPair(v).first;
    }
 
    void unionSets(int a, int b){
 
        a = findSet(a);
        b = findSet(b);
 
        if (a != b){
            if (sz[a] < sz[b]) swap(a, b);
            parent[b] = a;
            cnt[b] = -cnt[a] + cnt[b];
            sz[a] += sz[b];
        }
    }
 
    void query(int a){
        a = findSet(a);
        cnt[a] += 1;
    }
 
    int getCnt(int a){
        int p = findSet(a);
        return cnt[a] + (a != p ? cnt[p] : 0);
    }
};
 
int n, m, w[N];
DSU dsu;
 
int main()
{
    #ifdef Alex_PKZDL
    file;
    #endif // Alex_PKZDL
 
    ios_base::sync_with_stdio(false);
 
    cin >> n >> m;
 
    dsu.makeSets(n);
    int zerg = 0;
 
    for (int i = 0; i < m; ++i){
        int tp; cin >> tp;
        if (tp == 1){
            int x; cin >> x; x = (x + zerg) % n;
            dsu.query(x);
            zerg = (30 * zerg + 239) % mod;
        } else if (tp == 2){
            int x, y; cin >> x >> y;
            x = (x + zerg) % n;
            y = (y + zerg) % n;
            if (dsu.findSet(x) == dsu.findSet(y)) continue;
            dsu.unionSets(x, y);
            zerg = (zerg * 13 + 11) % mod;
        } else {
            int x; cin >> x; x = (x + zerg) % n;
            int cnt = dsu.getCnt(x) - w[x];
            w[x] = dsu.getCnt(x);
            zerg = int((100500LL * zerg + (long long) cnt) % (long long)mod);
            cout << cnt << endl;
        }
    }
    return 0;
}
