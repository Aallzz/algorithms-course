#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "rmq"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = (int)5e5 + 10;
constexpr int inf = (int)1e9 + 10;
constexpr int undefine = inf;
 
struct segments_tree {
private:
    int l, r, mn, sz, p, value;
    segments_tree *left, *right;
public:
    segments_tree(int l, int r) : l(l), r(r) {
        mn = inf;
        sz = 0;
        left = right = nullptr;
        value = p = undefine;
        if (l == r) sz = 1;
        if (l < r) {
            left = new segments_tree(l, (l + r) >> 1);
            right = new segments_tree(((l + r) >> 1) + 1, r);
            sz = left->sz + right->sz;
        }
    }
 
    segments_tree(int l, int r, int *a) : l(l), r(r) {
        mn = inf;
        sz = 0;
        value = p = undefine;
        left = right = nullptr;
        if (l == r) {
            sz = 1;
            value = a[l];
            mn = a[l];
        }
        if (l < r) {
            left = new segments_tree(l, (l + r) >> 1, a);
            right = new segments_tree(((l + r) >> 1) + 1, r, a);
            sz = left->sz + right->sz;
            mn = min(left->mn, right->mn);
        }
    }
 
    void push(segments_tree *t) {
        if (!t) return;
        if (t->p == undefine) return;
        if (t->sz != 1) {
            t->left->p = t->p;
            t->right->p = t->p;
        }
        t->mn = t->p;
        t->p = undefine;
    }
 
    void modify(int _l, int _r, int d) {
        push(this);
        if (l == _l && r == _r) {
            p = d;
            push(this);
        } else {
            if (_l <= left->r) left->modify(_l, min(left->r, _r), d);
            if (_r >= right->l) right->modify(max(right->l, _l), _r, d);
            push(left);
            push(right);
            mn = min(left->mn, right->mn);
        }
    }
 
    int getMin(int _l, int _r) {
        push(this);
        if (l == _l && r == _r) {
            return mn;
        }
        int res = undefine;
        if (_l <= left->r) res = min(res, left->getMin(_l, min(left->r, _r)));
        if (_r >= right->l) res = min(res, right->getMin(max(right->l, _l), _r));
        return res;
    }
};
 
segments_tree *t;
int n, a[N];
 
int main() {
    ios_base::sync_with_stdio(false);
 
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    t = new segments_tree(0, n - 1, a);
    string tp;
    int x, y;
    while (cin >> tp >> x >> y) {
        x--; y--;
        if (tp[0] == 'm') {
            cout << t->getMin(x, y) << "\n";
        } else {
            t->modify(x, x, y + 1);
        }
    }
 
    return 0;
}
