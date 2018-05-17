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
        if (cur->val <= key) {
            split(cur->right, key, cur->right, right);
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
 
    void put(node *&cur, int key) {
        if (cur == NULL) {
            cur = new node(key);
            return ;
        }
        node *l, *r, *m;
        split(cur, key, l, r);
        m = new node(key);
        merge(cur, l, m);
        merge(cur, cur, r);
    }
 
    int kth(node *cur, int nm) {
        while (cur != NULL) {
            int szLeft = getSz(cur->left);
            if (szLeft == nm) return cur->val;
 
            cur = szLeft > nm ? cur->left : cur->right;
            if (szLeft < nm)
                nm -= szLeft + 1;
        }
        return -1;
    }
 
    void del(node *&cur, int key) {
        if (cur == NULL) return ;
        node *l, *r, *m;
        split(cur, key-1, l, r);
        split(r, key, m, r);
        merge(cur, l, r);
    }
 
public:
 
    void put(int key) {
        put(root, key);
    }
 
    int kth(int nm) {
        return kth(root, nm);
    }
 
    void del(int key) {
        del(root, key);
    }
 
};
 
Treap tree;
 
int q;
 
int main() {
 
    cin >> q;
    while (q--) {
        int tp, a;
        cin >> tp >> a;
        if (tp == 1) {
            tree.put(-a);
        } else if (tp == -1){
            tree.del(-a);
        } else {
            cout << -tree.kth(a - 1) << endl;
        }
    }
    return 0;
}
