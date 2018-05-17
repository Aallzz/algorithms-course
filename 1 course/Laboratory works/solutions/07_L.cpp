#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "find2d"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int n = (1 << 17);
 
unsigned int z[n + 10];
unsigned int q, a, b;
unsigned int cur;
 
inline unsigned int nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}
 
inline unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}
 
class segments_tree {
private:
    unsigned int l, r, sz;
    vector<unsigned int> a;
    vector<unsigned int> reference_to_left;
    vector<unsigned int> reference_to_right;
    segments_tree *left, *right;
 
    vector<unsigned int> calc_links(vector<unsigned int>& a, vector<unsigned int>& b) {
        vector<unsigned int> res(a.size() + 1);
        unsigned int nxt = 0;
        for (unsigned int i = 0; i < a.size(); ++i) {
            while (nxt < b.size() && b[nxt] < a[i]) ++ nxt;
            res[i] = nxt;
        }
        res[a.size()] = b.size();
        return res;
    }
 
public:
    segments_tree(unsigned int l, unsigned int r, unsigned int *c) : l(l), r(r) {
        sz = 0;
        left = right = nullptr;
        if (l == r) {
            sz = 1;
            a.push_back(c[l]);
        }
        if (l < r) {
            left = new segments_tree(l, (l + r) >> 1, c);
            right = new segments_tree(((l + r) >> 1) + 1, r, c);
            merge (left->a.begin(), left->a.end(), right->a.begin(), right->a.end(), back_inserter(a));
//            a.resize(unique(a.begin(), a.end()) - a.begin());
        }
    }
 
 
    unsigned int getCount(unsigned int _l, unsigned int _r, unsigned int mn, unsigned int mx) {
        if (_l == l && r == _r) {
            auto lb = lower_bound(a.begin(), a.end(), mn),
                 rb = upper_bound(a.begin(), a.end(), mx);
            return rb - lb;
        }
        unsigned int res = 0;
        if (_l <= left->r) res += left->getCount(_l, min(left->r, _r), mn, mx);
        if (_r >= right->l) res += right->getCount(max(right->l, _l), _r, mn, mx);
        return res;
    }
};
 
segments_tree *t;
 
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
 
    cin >> q;
    cin >> a >> b;
 
    for (int i = 0; i < n; ++i) {
        z[i] = nextRand24();
    }
 
    t = new segments_tree(0, n - 1, z);
 
    unsigned int l, r, x, y, res = 0;
 
    for (unsigned int i = 0; i < q; ++i) {
        l = nextRand17();
        r = nextRand17();
        if (l > r) swap(l, r);
        x = nextRand24();
        y = nextRand24();
        if (x > y) swap(x, y);
        unsigned int cur = t->getCount(l, r, x, y);
        res += cur;
        b += cur;
    }
 
    cout << res << endl;
 
//    int m; cin >> m;
//    for (int i = 0; i < m; ++i) cin >> z[i];
//
//    t = new segments_tree(0, m - 1, z);
//    int q; cin >> q;
//    while (q--) {
//        int l, r, x, y; cin >> l >> r >> x >> y;
//        cout << t->getCount(l, r, x, y) << endl;
//    }
    return 0;
}
