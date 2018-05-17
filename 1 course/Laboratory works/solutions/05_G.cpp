#include <bits/stdc++.h>
 
using namespace std;
 
 
const long long mod = (long long)1e9;
 
struct Treap {
 
public:
 
    struct node {
        long long sm;
        int sz, y, val;
        bool rev;
 
        node* left;
        node* right;
 
        node(int val) : val(val) {
            y = rand() | (rand() << 16);
            left = right = NULL;
            sz = 1;
            sm = val;
        }
    };
 
    node *root;
 
    int getSz(node *t) {
        return (t == NULL ? 0 : t->sz);
    }
 
    long long getSm(node *t) {
        return (t == NULL ? 0LL : t->sm);
    }
 
    void recalc(node *t) {
        if (t == NULL) return ;
        t->sz = getSz(t->left) + getSz(t->right) + 1;
        t->sm = t->val + getSm(t->left) + getSm(t->right);
    }
 
    void split(node *cur, int key, node *&left, node *&right) {
        if (cur == NULL) {
            left = right = NULL;
            return ;
        }
        if (cur->val <= key) {
            split(cur->right, key, cur->right, right);
            left = cur;
            recalc(left);
        } else {
            split(cur->left, key, left, cur->left);
            right = cur;
            recalc(right);
        }
    }
 
    void merge(node *&cur, node *left, node *right) {
        if (left == NULL || right == NULL) {
            cur = (left == NULL ? right : left);
            return ;
        }
 
        if (left->y > right->y) {
            merge(left->right, left->right, right);
            cur = left;
        } else {
            merge(right->left, left, right->left);
            cur = right;
        }
        recalc(cur);
    }
 
    void put(node *&cur, int key) {
        if (cur == NULL) {
            cur = new node(key);
            return ;
        }
        node *l, *r, *m;
        split(cur, key - 1, l, r);
        split(r, key, m, r);
        if (m == NULL)
            m = new node(key);
        merge(cur, l, m);
        merge(cur, cur, r);
    }
 
    void del(node *&cur, int key) {
        if (cur == NULL) return ;
        node *l, *r, *m;
        split(cur, key-1, l, r);
        split(r, key, m, r);
        merge(cur, l, r);
    }
 
    long long getSum(node *&cur, int a, int b) {
        node *l, *r, *m;
        split(cur, a - 1, l, r);
        split(r, b, m, r);
        long long res = getSm(m);
        merge(cur, l, m);
        merge(cur, cur, r);
        return res;
    }
 
public:
 
    void put(int key) {
        put(root, key);
    }
 
    void del(int key) {
        del(root, key);
    }
 
    long long getSum(int a, int b) {
        return getSum(root, a, b);
    }
 
};
 
Treap tree;
 
int q;
 
int main() {
 
    ios_base::sync_with_stdio(false);
    cin >> q;
    char pq = '+';
    long long pans = 0;
 
    while (q--) {
        char tp;
        cin >> tp;
        if (tp == '+') {
            int x; cin >> x;
            if (pq == '+') {
                tree.put(x);
            } else {
                tree.put((int)((x + pans) % mod));
            }
        } else {
            int l, r; cin >> l >> r;
            long long ans = tree.getSum(l, r);
            pans = ans;
            cout << ans << endl;
        }
        pq = tp;
    }
    return 0;
}
