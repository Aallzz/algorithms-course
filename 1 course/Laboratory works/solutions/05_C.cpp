#include <bits/stdc++.h>
 
using namespace std;
 
class Treap {
 
public:
 
    struct node {
        int val, y, sz;
        bool rev;
 
        node* left;
        node* right;
 
        node(int val) : val(val) {
            y = rand() | (rand() << 16);
            left = right = NULL;
            sz = 1;
        }
    };
 
private:
 
    node *root;
 
    int getSz(node *t) {
        return (t == NULL ? 0 : t->sz);
    }
 
    void recalc(node *t) {
        if (t == NULL) return ;
        t->sz = getSz(t->left) + getSz(t->right) + 1;
    }
 
    void split(node *cur, int key, node *&left, node *&right) {
        if (cur == NULL) {
            left = right = NULL;
            return ;
        }
        int curidx = getSz(cur->left) + 1;
        if (curidx <= key) {
            split(cur->right, key - curidx, cur->right, right);
            left = cur;
        } else {
            split(cur->left, key, left, cur->left);
            right = cur;
        }
        recalc(cur);
        recalc(left);
        recalc(right);
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
        recalc(left);
        recalc(right);
    }
 
    void put(node *&cur, int pos, int key) {
        if (cur == NULL) {
            cur = new node(key);
            return ;
        }
        node *l, *r, *m;
        split(cur, pos, l, r);
        m = new node(key);
        merge(cur, l, m);
        merge(cur, cur, r);
    }
 
    void relocate(node *&cur, int a, int b) {
        node *l, *r, *m;
        split(cur, a, l, r);
        split(r, b - a, m, r);
        merge(cur, m, l);
        merge(cur, cur, r);
    }
 
    int getKey(node *&cur, int pos) {
        node *l, *r, *m;
        split(cur, pos, l, r);
        split(r, 1, m, r);
        int res = m->val;
        merge(cur, l, m);
        merge(cur, cur, r);
        return res;
    }
 
public:
 
    void put(int pos, int key) {
        put(root, pos, key);
    }
 
    void relocate(int a, int b) {
        relocate(root, a, b);
    }
 
    int getKey(int pos) {
        return getKey(root, pos);
    }
};
 
Treap tree;
int n, q;
 
int main() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
        tree.put(i, i);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r; l--;
        tree.relocate(l, r);
    }
    for (int i = 0; i < n; ++i) {
        cout << tree.getKey(i) + 1 << " ";
    }
    cout << endl;
    return 0;
}
