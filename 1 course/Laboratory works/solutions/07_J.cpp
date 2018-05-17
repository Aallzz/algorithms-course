#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "windows"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = (int)5e4 + 10;
constexpr int inf = (int)1e9 + 10;
 
vector<pair<int, int>> e;
int n;
 
struct rectangle{
    int x, y, xx, yy;
} a[N];
 
class segments_tree {
private:
    int l, r, sz;
    int add;
    pair<int, int> mx;
    segments_tree *left, *right;
 
public:
    segments_tree(int l, int r) : l(l), r(r) {
        sz = add = 0;
        left = right = nullptr;
        mx = {0, 0};
        if (l == r) sz = 1, mx = {0, l};
        if (l < r) {
            left = new segments_tree(l, (l + r) >> 1);
            right = new segments_tree(((l + r) >> 1) + 1, r);
            sz = left->sz + right->sz;
            mx = max(left->mx, right->mx);
        }
    }
 
    void push(segments_tree *t) {
        if (!t) return;
        if (t->add == 0) return;
        if (t->sz != 1) {
            t->left->add += t->add;
            t->right->add += t->add;
        }
        t->mx.first += t->add;
        t->add = 0;
    }
 
    void modify(int _l, int _r, int d) {
        push(this);
        if (_l == l && r == _r)  {
            add += d;
            push(this);
            return ;
        }
        if (_l <= left->r) left->modify(_l, min(left->r, _r), d);
        if (_r >= right->l) right->modify(max(right->l, _l), _r, d);
        push(left);
        push(right);
        mx = max(left->mx, right->mx);
    }
 
    pair<int, int> getMax(int _l, int _r) {
        push(this);
        if (_l == l && r == _r) return mx;
        pair<int, int> res = {-inf, -inf};
        if (_l <= left->r) res = max(res, left->getMax(_l, min(left->r, _r)));
        if (_r >= right->l) res = max(res, right->getMax(max(right->l, _l), _r));
        return res;
    }
};
 
segments_tree *t;
vector<int> c;
 
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
 
    cin >> n;
    t = new segments_tree(0, n * 5);
    for (int i = 1; i <= n; ++i) {
        int x, y, xx, yy; cin >> x >> y >> xx >> yy;
        a[i] = {x, y, xx, yy};
        c.push_back(x);
        c.push_back(y);
        c.push_back(xx);
        c.push_back(yy);
    }
 
    sort(c.begin(), c.end());
    c.resize(unique(c.begin(), c.end()) - c.begin());
 
    for (int i = 1; i <= n; ++i) {
        a[i].x = lower_bound(c.begin(), c.end(), a[i].x) - c.begin();
        a[i].y = lower_bound(c.begin(), c.end(), a[i].y) - c.begin();
        a[i].xx = lower_bound(c.begin(), c.end(), a[i].xx) - c.begin();
        a[i].yy = lower_bound(c.begin(), c.end(), a[i].yy) - c.begin();
        e.push_back({a[i].x, -i});
        e.push_back({a[i].xx, i});
    }
    sort(e.begin(), e.end());
 
    int ans = 0;
    int xxx = 0, yyy = 0;
 
    for (auto cur : e) {
        int tp = cur.second;
        int i = abs(tp);
        int y = a[i].y;
        int yy = a[i].yy;
        if (tp > 0) { // close
            t->modify(y, yy, -1);
        } else {
            t->modify(y, yy, 1);
            auto res = t->getMax(0, 5 * n);
            if (res.first > ans) {
                ans = res.first;
                xxx = cur.first;
                yyy = res.second;
            }
        }
    }
 
    cout << ans << endl;
    cout << c[xxx] << " " << c[yyy] << endl;
    return 0;
}
