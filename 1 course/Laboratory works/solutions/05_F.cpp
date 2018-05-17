#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)4e5 + 10;
 
class Treap {
 
public:
 
    struct node {
        int val, y, sz, upd;
        bool rev;
 
        node* left;
        node* right;
 
        node(int val) : val(val) {
            upd = -1;
            y = rand() | (rand() << 16);
            left = right = NULL;
            sz = 1;
        }
    };
 
private:
 
    node *root;
 
    void push(node *t) {
        if (t == NULL) return ;
        if (t->upd == -1) return ;
        if (t->left != NULL) t->left->upd = t->upd;
        if (t->right != NULL) t->right->upd = t->upd;
        t->val = t->upd;
        t->upd = -1;
    }
 
    int getSz(node *t) {
        return (t == NULL ? 0 : t->sz);
    }
 
    void recalc(node *t) {
        if (t == NULL) return ;
        t->sz = getSz(t->left) + getSz(t->right) + 1;
    }
 
    void split(node *cur, int key, node *&left, node *&right) {
        push(cur);
        if (cur == NULL) {
            left = right = NULL;
            return ;
        }
        int curidx = getSz(cur->left) + 1;
        if (curidx <= key) {
            split(cur->right, key - curidx, cur->right, right);
            left = cur;
            recalc(left);
        } else {
            split(cur->left, key, left, cur->left);
            right = cur;
            recalc(right);
        }
    }
 
    void merge(node *&cur, node *left, node *right) {
        push(left);
        push(right);
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
 
    int getKey(node *&cur, int pos) {
        node *l, *r, *m;
        split(cur, pos, l, r);
        split(r, 1, m, r);
        int res = (m == NULL ? 0 : m->val);
        merge(cur, l, m);
        merge(cur, cur, r);
        return res;
    }
 
    void shift(node *&cur, int a, int b) {
        node *l, *r, *m, *mm;
        split(cur, b, l, r);
        split(r, 1, m, r);
        split(l, a, l, mm);
        merge(cur, l, m);
        merge(cur, cur, mm);
        merge(cur, cur, r);
    }
 
    void update(node *&cur, int a, int b, int x) {
        node *l, *r, *m;
        l = r = m = NULL;
        split(cur, a, l, r);
        split(cur, b - a, m, r);
        m->upd = x;
        merge(cur, l, m);
        merge(cur, cur, r);
    }
 
    void del(node *&cur, int a) {
        node *l, *r, *m;
        l = r = m = NULL;
        split(cur, a, l, r);
        split(r, 1, m, r);
        delete m;
        merge(cur, l, r);
    }
 
public:
 
    void put(int pos, int key) {
        put(root, pos, key);
    }
 
    void shift(int a, int b) {
        shift(root, a, b);
    }
 
    int getKey(int pos) {
        return getKey(root, pos);
    }
 
    void update(int a, int b, int x) {
        update(root, a, b, x);
    }
 
    void del(int pos) {
        del(root, pos);
    }
};
 
Treap treeElements;
Treap treeNextZero;
Treap treePrevZero;
 
int n, q;
 
int main() {
 
    for (int i = 0; i < N; ++i) treeNextZero.put(i, i + 1);
    for (int i = 0; i < N; ++i) treePrevZero.put(i, i - 1);
    for (int i = 0; i < N; ++i) treeElements.put(i, 0);
 
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        int pos; cin >> pos;
        int nxtZero = treeNextZero.getKey(pos);
        int prvZero = treePrevZero.getKey(pos);
 
        if (treeElements.getKey(pos) == 0) {
            treeElements.del(pos);
            treeNextZero.update(prvZero, nxtZero, nxtZero);
            treePrevZero.update(prvZero + 1, nxtZero + 1, prvZero);
        } else {
            treeElements.del(nxtZero);
            int nxtnxtZero = treeNextZero.getKey(nxtZero);
            treeNextZero.update(prvZero, nxtnxtZero, nxtnxtZero);
            treePrevZero.update(prvZero + 1, nxtnxtZero + 1, prvZero);
        }
        treeElements.put(pos, i);
    }
 
    int nxt = treeElements.getKey(1);
 
    vector<int> ans;
 
    for (int i = 1; i <= q || nxt != 0; ++i) {
        ans.push_back(nxt);
        nxt = treeElements.getKey(i + 1);
    }
 
    while (ans.back() == 0) ans.pop_back();
 
    cout << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) cout << ans[i] << " ";
    cout << endl;
    return 0;
}
