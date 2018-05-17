#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "caves"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr long long N = (long long)3e5 + 10;
constexpr long long inf = (long long)1e18 + 10;
 
class segments_tree {
private:
    long long l, r, sz;
    long long p;
    long long v;
    long long mn;
    segments_tree *left, *right;
public:
    segments_tree(long long l, long long r) : l(l), r(r) {
        p = -1;
        left = right = nullptr;
        mn = 0;
        p = -1;
        v = sz = 0;
        if (l == r) sz = 1, mn = 0;
        if (l < r) {
            left = new segments_tree(l, (l + r) >> 1);
            right = new segments_tree(((l + r) >> 1) + 1, r);
            mn = max(left->mn, right->mn);
            sz = left->sz + right->sz;
        }
    }
 
    void push(segments_tree *t) {
        if (!t) return;
        if (t->p == -1) return;
        if (t->p == 0) {
            if (t->sz != 1) {
                t->left->p = t->p;
                t->right->p = t->p;
                t->left->v = t->v;
                t->right->v = t->v;
            }
            t->mn = t->v;
            t->p = -1;
            t->v = 0;
        } else {
            if (t->sz != 1) {
                if (t->left->p == 0) {
                    t->left->v += t->v;
                } else {
                    t->left->p = t->p;
                    t->left->v += t->v;
                }
                if (t->right->p == 0) {
                    t->right->v += t->v;
                } else {
                    t->right->p = t->p;
                    t->right->v += t->v;
                }
            }
            t->mn += t->v;
            t->p = -1;
            t->v = 0;
        }
    }
 
    void update(long long _l, long long _r, long long d) {
        push(left);
        push(right);
        push(this);
        if (_l == l && r == _r) {
            p = 0;
            v = d;
            push(this);
        } else {
            if (_l <= left->r) left->update(_l, min(left->r, _r), d);
            if (_r >= right->l) right->update(max(right->l, _l), _r, d);
            push(left);
            push(right);
            mn = max(left->mn, right->mn);
        }
    }
 
    void modify(long long _l, long long _r, long long d) {
        push(left);
        push(right);
        push(this);
        if (_l == l && r == _r) {
            p = 1;
            v += d;
            push(this);
        } else {
            if (_l <= left->r) left->modify(_l, min(left->r, _r), d);
            if (_r >= right->l) right->modify(max(right->l, _l), _r, d);
            push(left);
            push(right);
            mn = max(left->mn, right->mn);
        }
    }
 
    long long getMin(long long _l, long long _r) {
        push(left);
        push(right);
        push(this);
        if (_l == l && _r == r) return mn;
        long long res = 0;
        if (_l <= left->r) res = max(res, left->getMin(_l, min(left->r, _r)));
        if (_r >= right->l) res = max(res, right->getMin(max(right->l, _l), _r));
        return res;
    }
} ;
long long chainRoot[N],chain[N],chainSize[N],chainpos[N], chainNum;
long long sz[N], tin[N], tout[N], timer, p[N];
long long n,q;
vector <long long> g[N];
segments_tree *tree[N];
 
void dfs(long long v, long long prev = -1)
{
    sz[v] = 1;
    tin[v] = timer++;
    p[v] = prev;
    for (int i = 0; i < (int)g[v].size(); ++i)
    {
        long long to = g[v][i];
        if (to == prev) continue;
        dfs(to, v);
        sz[v] += sz[to];
    }
    tout[v] = timer++;
}
 
long long newChain(long long to)
{
    chainRoot[++chainNum] = to;
    return chainNum;
}
 
bool ancestor(long long a, long long b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}
 
bool isHeavy(long long from, long long to)
{
    return sz[to] << 1 >= sz[from];
}
 
void buildChain(long long v, long long curChain)
{
    chain[v] = curChain;
    chainSize[curChain]++;
    chainpos[v] = chainSize[curChain];
    for (int i = 0; i < (int)g[v].size(); ++i)
    {
        if (g[v][i] == p[v]) continue;
        if (isHeavy(v, g[v][i]))
            buildChain(g[v][i], curChain);
        else
            buildChain(g[v][i], newChain(g[v][i]));
    }
}
 
long long getMax(long long a, long long b)
{
    long long res = 0;
    while (true)
    {
        long long curChain = chain[a];
        if (ancestor(chainRoot[curChain],b)) break;
        res = max(res,tree[curChain]->getMin(1, chainpos[a]));
        a = p[chainRoot[curChain]];
    }
    while (true)
    {
        long long curChain = chain[b];
        if (ancestor(chainRoot[curChain],a)) break;
        res = max(res,tree[curChain]->getMin(1, chainpos[b]));
        b = p[chainRoot[curChain]];
    }
    long long from = chainpos[a], to = chainpos[b];
    if (from > to) swap(from,to);
    res = max(res, tree[chain[a]]->getMin(from,to));
    return res;
}
 
void modifyWay(long long a, long long b, long long d)
{
    while (true)
    {
        long long curChain = chain[a];
        if (ancestor(chainRoot[curChain],b)) break;
        tree[curChain]->modify(1, chainpos[a], d);
        a = p[chainRoot[curChain]];
    }
    while (true)
    {
        long long curChain = chain[b];
        if (ancestor(chainRoot[curChain],a)) break;
        tree[curChain]->modify(1, chainpos[b], d);
        b = p[chainRoot[curChain]];
    }
    long long from = chainpos[a], to = chainpos[b];
    if (from > to) swap(from,to);
    tree[chain[a]]->modify(from, to, d);
}
 
int main() {
 
    ios_base::sync_with_stdio(false);
    #ifdef Alex_PKZDL
//        freopen("input.txt", "r", stdin);
//        freopen("output.txt", "w", stdout);
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
//        freopen(taski, "r", stdin);
//        freopen(tasko, "w", stdout);
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    cin >> n;
    for (long long i = 1; i < n; ++i) {
        long long x, y; cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
 
    dfs(1);
    buildChain(1, newChain(1));
 
    for (long long i = 1; i <= chainNum; ++i)
        tree[i] = new segments_tree(1, chainSize[i]);
 
 
    cin >> q;
    while(q--) {
        char c; cin >> c;
        if (c == 'I') {
            long long u, d; cin >> u >> d;
            modifyWay(u, u, d);
        } else {
            long long x, y; cin >> x >> y;
            cout << getMax(x, y) << endl;
        }
    }
    return 0;
}
