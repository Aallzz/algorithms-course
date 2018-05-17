#include <bits/stdc++.h>
 
using namespace std;
 
const long long N = (long long)1e6 + 10;
const long long M = (long long)1e3 + 10;
const long long inf = (long long)1e9 + 10;
const long long mod = (long long)239017;
const long long mmod = (long long)1e9 + 1;
 
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
 
 
struct heap{
    long long key, d;
    heap *left, *right;
};
 
heap* link[N];
long long sz = 1;
 
long long dist(heap *hp){
    return (hp == NULL ? 0 : hp->d);
}
 
long long getKey(heap *hp){
    return (hp == NULL ? -1 : hp->key);
}
 
 
heap* merge(heap *x, heap *y){
 
    if (x == NULL && y == NULL) return NULL;
    if (x == NULL) return new heap {y->key, y->d, y->left, y->right};
    if (y == NULL) return new heap {x->key, x->d, x->left, x->right};
 
    if (getKey(y) < getKey(x)) swap(x, y);
 
 
    heap *newx = new heap{getKey(x), x->d, x->left, merge(x->right, y)};
 
    if (dist(newx->right) > dist(newx->left))
        swap(newx->left, newx->right);
    newx->d = min(dist(newx->left), dist(newx->right)) + 1;
    return newx;
}
 
long long coolMerge(heap *x, heap *y){
    link[sz++] = merge(x, y);
    return getKey(link[sz - 1]);
}
 
long long insert(heap *hp, long long x){
    heap *h = new heap {x, 0, NULL, NULL};
    link[sz++] = merge(hp, h);
    return getKey(link[sz - 1]);
}
 
long long getMin(heap *hp){
    if (hp == NULL) {
        link[sz++] = NULL;
        return -1;
    }
    long long res = getKey(hp);
    link[sz++] = merge(hp->left, hp->right);
    return res;
}
 
long long n;
 
int main()
{
    #ifdef Alex_PKZDL
    file;
    #endif // Alex_PKZDL
 
    for (int i = 0; i < N; ++i) link[i] = NULL;
    ios_base::sync_with_stdio(false);
 
    cin >> n;
    long long s = 0;
    for (long long i = 1; i <= n; ++i){
        long long tp; cin >> tp;
        long long res;
        if (tp == 1){
            long long v, x; cin >> v >> x;
            v = (v + s) % i;
            x = (x + 17LL * s) % mmod;
            res = insert(link[v], x);
        } else if (tp == 2){
            long long v, u; cin >> v >> u;
            v = (v + s) % i;
            u = (u + 13LL * s) % i;
            res = coolMerge(link[v], link[u]);
        } else {
            long long v; cin >> v;
            v = (v + s) % i;
            res = getMin(link[v]);
        }
        if (res != -1){
            cout << res << endl;
        } else {
            cout << "empty" << endl;
            res = 0;
        }
        s = (s + res) % mod;
    }
    return 0;
}
