#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "parking"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr long long linf = (long long)1e18 + 10;
constexpr int inf = (int)1e9 + 10;
constexpr int N = (int)1e5 + 10;
 
class segments_tree {
private:
    int l, r, sz;
    pair<int, int> mn;
    segments_tree *left, *right;
public:
    segments_tree(int l, int r) : l(l), r(r) {
        sz = 0;
        mn = {inf, inf};
        left = right = NULL;
        if (l == r) {
            sz = 1;
            mn = {-inf, l};
        }
        if (l < r) {
            left = new segments_tree(l, (l + r) >> 1);
            right = new segments_tree(((l + r) >> 1) + 1, r);
            mn = min(left->mn, right->mn);
            sz = left->sz + right->sz;
        }
    }
 
    void modify(int pos, int d) {
        if (pos == l && pos == r) {
            mn = {d, pos};
        } else {
            if (pos <= left->r) left->modify(pos, d);
            else right->modify(pos, d);
            mn = min(left->mn, right->mn);
        }
    }
 
    pair<int, int> getMin(int _l, int _r) {
        if (_l == l && r == _r) {
            return mn;
        }
        pair<int, int> res = {inf, inf};
        if (_l <= left->r) res = min(res, left->getMin(_l, min(left->r, _r)));
        if (_r >= right->l) res = min(res, right->getMin(max(right->l, _l), _r));
        return res;
    }
};
 
int n, m;
segments_tree *t;
 
int main() {
    ios_base::sync_with_stdio(false);
 
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    cin >> n >> m;
    t = new segments_tree(0, n - 1);
    for (int i = 0; i < m; ++i) {
        string s; cin >> s;
        if (s[1] == 'n') {
            int x; cin >> x; x--;
            auto r = t->getMin(x, n - 1);
            if (r.first == inf) {
                r = t->getMin(0, n - 1);
            }
            cout << r.second + 1 << "\n";
            t->modify(r.second, inf);
        } else {
            int x; cin >> x; x--;
            t->modify(x, -inf);
        }
    }
    return 0;
}
