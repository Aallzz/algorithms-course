#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "crypto"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr long long N = (long long)5e5 + 10;
 
struct matrix {
    int mod;
    int mtrx[2][2];
 
    matrix() : mod(1) {mtrx[0][0] = mtrx[0][1] = mtrx[1][0] = mtrx[1][1] = 0;};
 
 
    matrix(int mod) : mod(mod) {
        mtrx[0][0] = mtrx[0][1] = mtrx[1][0] = mtrx[1][1] = 0;
    }
 
    matrix(matrix const& other) {
        mod = other.mod;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                mtrx[i][j] = other.mtrx[i][j];
    }
 
    matrix& operator =(matrix const& other) {
        mod = other.mod;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                mtrx[i][j] = other.mtrx[i][j];
        return *this;
    }
 
    matrix& operator *=(matrix const& other) {
        matrix temp(mod);
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    (temp.mtrx[i][j] += mtrx[i][k] * other.mtrx[k][j]) %= mod;
                }
            }
        }
        *this = temp;
        return *this;
    }
 
    void write_matrix(ofstream& cout) {
        for (int i = 0; i < 2; ++i, cout << "\n")
            for (int j = 0; j < 2; ++j)
                cout << mtrx[i][j] << " ";
    }
 
    friend matrix operator *(matrix a, matrix const& b) {
        return a *= b;
    }
};
 
matrix make_E(int mod) {
    matrix temp(mod);
    for (int i = 0; i < 2; ++i) temp.mtrx[i][i] = 1;
    return temp;
}
 
matrix read_matrix(int mod, ifstream& cin) {
    matrix temp(mod);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            cin >> temp.mtrx[i][j];
    return temp;
}
 
struct segments_tree {
private:
    int l, r, mod;
    matrix ml;
    segments_tree *left, *right;
public:
    segments_tree(int l, int r, int mod) : l(l), r(r), mod(mod) {
       ml.mod = mod;
       left = right = NULL;
       if (l < r) {
            left = new segments_tree(l, (l + r) >> 1, mod);
            right = new segments_tree(((l + r) >> 1) + 1, r, mod);
       }
    }
 
    void modify(int pos, matrix const& m) {
        if (pos == l && pos == r) {
            ml = m;
            return ;
        }
        if (pos <= left->r) left->modify(pos, m);
        if (pos >= right->l) right->modify(pos, m);
        ml = left->ml * right->ml;
    }
 
    matrix getMul(int _l, int _r) {
        if (_l == l && r == _r) return ml;
        matrix res = make_E(mod);
        if (_l <= left->r) res *= left->getMul(_l, min(left->r, _r));
        if (_r >= right->l) res *= right->getMul(max(right->l, _l), _r);
        return res;
    }
};
 
segments_tree *t;
int r, n, m;
 
int main() {
 
    #ifdef Alex_PKZDL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif // Alex_PKZDL
 
    scanf("%d%d%d", &r, &n, &m);
    t = new segments_tree(0, n - 1, r);
    matrix c;
    c.mod = r;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d%d%d", &c.mtrx[0][0], &c.mtrx[0][1], &c.mtrx[1][0], &c.mtrx[1][1]);
        t->modify(i, c);
    }
 
    for (int i = 0; i < m; ++i) {
        int l, r; scanf("%d%d", &l, &r); l--; r--;
        c = t->getMul(l, r);
        printf("%d %d\n%d %d\n\n", c.mtrx[0][0], c.mtrx[0][1], c.mtrx[1][0], c.mtrx[1][1]);
    }
    return 0;
}
