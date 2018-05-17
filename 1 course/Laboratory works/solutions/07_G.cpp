#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "rmq2"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr long long inf = (long long)1e18 + 10;
constexpr int N = (int)1e5 + 10;
 
class segments_tree {
private:
    int l, r, sz;
    int p;
    long long v;
    long long mn;
    segments_tree *left, *right;
public:
    segments_tree(int l, int r, long long* a) : l(l), r(r) {
        p = -1;
        left = right = nullptr;
        mn = inf;
        p = -1;
        v = sz = 0;
        if (l == r) sz = 1, mn = a[l];
        if (l < r) {
            left = new segments_tree(l, (l + r) >> 1, a);
            right = new segments_tree(((l + r) >> 1) + 1, r, a);
            mn = min(left->mn, right->mn);
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
 
    void update(int _l, int _r, int d) {
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
            mn = min(left->mn, right->mn);
        }
    }
 
    void modify(int _l, int _r, int d) {
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
            mn = min(left->mn, right->mn);
        }
    }
 
    long long getMin(int _l, int _r) {
        push(left);
        push(right);
        push(this);
        if (_l == l && _r == r) return mn;
        long long res = inf;
        if (_l <= left->r) res = min(res, left->getMin(_l, min(left->r, _r)));
        if (_r >= right->l) res = min(res, right->getMin(max(right->l, _l), _r));
        return res;
    }
} ;
 
segments_tree *t;
int n;
long long a[N];
 
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
    while (cin >> tp) {
        if (tp[0] == 'a') {
            int l, r, x; cin >> l >> r >> x; l--; r--;
            t->modify(l, r, x);
        }
        if (tp[0] == 's') {
            int l, r, x; cin >> l >> r >> x; l--; r--;
            t->update(l, r, x);
        }
        if (tp[0] == 'm') {
            int l, r; cin >> l >> r; l--; r--;
            cout << t->getMin(l, r) << "\n";
        }
    }
 
    return 0;
}
