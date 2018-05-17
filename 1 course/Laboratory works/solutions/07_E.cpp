#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "rsq"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr long long N = (long long)5e5 + 10;
constexpr long long inf = (long long)1e18 + 10;
constexpr long long undefine = inf;
 
struct segments_tree {
private:
    long long l, r, sm, sz, p, value;
    segments_tree *left, *right;
public:
    segments_tree(long long l, long long r) : l(l), r(r) {
        sm = 0;
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
 
    segments_tree(long long l, long long r, long long *a) : l(l), r(r) {
        sm = 0;
        sz = 0;
        value = p = undefine;
        left = right = nullptr;
        if (l == r) {
            sz = 1;
            value = a[l];
            sm = a[l];
        }
        if (l < r) {
            left = new segments_tree(l, (l + r) >> 1, a);
            right = new segments_tree(((l + r) >> 1) + 1, r, a);
            sz = left->sz + right->sz;
            sm = left->sm + right->sm;
        }
    }
 
    void push(segments_tree *t) {
        if (!t) return;
        if (t->p == undefine) return;
        if (t->sz != 1) {
            t->left->p = t->p;
            t->right->p = t->p;
        }
        t->sm = t->p * t->sz;
        t->p = undefine;
    }
 
    void modify(long long _l, long long _r, long long d) {
        push(this);
        if (l == _l && r == _r) {
            p = d;
            push(this);
        } else {
            if (_l <= left->r) left->modify(_l, min(left->r, _r), d);
            if (_r >= right->l) right->modify(max(right->l, _l), _r, d);
            push(left);
            push(right);
            sm = left->sm + right->sm;
        }
    }
 
    long long getSum(long long _l, long long _r) {
        push(this);
        if (l == _l && r == _r) {
            return sm;
        }
        long long res = 0;
        if (_l <= left->r) res += left->getSum(_l, min(left->r, _r));
        if (_r >= right->l) res += right->getSum(max(right->l, _l), _r);
        return res;
    }
};
 
segments_tree *t;
long long n, a[N];
 
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
    for (long long i = 0; i < n; ++i) cin >> a[i];
    t = new segments_tree(0, n - 1, a);
    string tp;
    long long x, y;
    while (cin >> tp >> x >> y) {
        x--; y--;
        if (tp[1] == 'u') {
            cout << t->getSum(x, y) << "\n";
        } else {
            t->modify(x, x, y + 1);
        }
    }
 
    return 0;
}
