#include <bits/stdc++.h>
 
using namespace std;
 
class BST {
 
public:
 
    struct node {
        int key;
        node *left, *right;
 
        node(int key) : key(key) {
            left = right = NULL;
        }
    };
 
private:
 
    node *root;
 
    node* get(node *cur, int k) {
        if (cur == NULL) return NULL;
        if (k < cur->key)
            return get(cur->left, k);
        else if (k > cur->key)
            return get(cur->right, k);
        else return cur;
    }
 
    node* put(node *cur, int k) {
        if (cur == NULL) {
            return new node(k);
        }
 
        if (k < cur->key) {
            cur->left = put(cur->left, k);
        } else if (k > cur->key) {
            cur->right = put(cur->right, k);
        }
 
        return cur;
    }
 
    node* getMin(node *cur) {
        if (cur->left == NULL) return cur;
        else return getMin(cur->left);
    }
 
    node* delMin(node *cur) {
        if (cur->left == NULL) return cur->right;
        cur->left = delMin(cur->left);
        return cur;
    }
 
    node* del(node *cur, int k) {
        if (cur == NULL) return NULL;
        if (k < cur->key) {
            cur->left = del(cur->left, k);
        } else if (k > cur->key) {
            cur->right = del(cur->right, k);
        } else {
            if (cur->right == NULL) return cur->left;
            if (cur->left == NULL) return cur->right;
            node *tmp = cur;
            cur = getMin(cur->right);
            cur->right  = delMin(tmp->right);
            cur->left = tmp->left;
        }
        return cur;
    }
 
    node* prev(node* cur, int k) {
        if (cur == NULL) return NULL;
        if (k < cur->key) {
            return prev(cur->left, k);
        } else if (k == cur->key) {
            return cur;
        } else {
            node *tmp = prev(cur->right, k);
            if (tmp != NULL) return tmp;
            else return cur;
        }
    }
 
    node* next(node *cur, int k) {
        if (cur == NULL) return NULL;
        if (k > cur->key) {
            return next(cur->right, k);
        } else if (k == cur->key) {
            return cur;
        } else {
            node *tmp = next(cur->left, k);
            if (tmp != NULL) return tmp;
            else return cur;
        }
    }
 
public:
 
    BST() {};
 
    int get(int k) {
        return get(root, k)->key;
    }
 
    void put(int k) {
        root = put(root, k);
    }
 
    bool contains(int k) {
        return get(root, k) != NULL;
    }
 
    void del(int k) {
        root = del(root, k);
    }
 
    node* prev(int k) {
        return prev(root, k);
    }
 
    node* next(int k) {
        return next(root, k);
    }
 
};
 
BST tree;
 
int main() {
 
    string s;
    int a;
    while (cin >> s >> a) {
        if (s[0] == 'i') {
            tree.put(a);
        } else if (s[0] == 'd') {
            tree.del(a);
        } else if (s[0] == 'e') {
            cout << (tree.contains(a) ? "true" : "false") << endl;
        } else if (s[0] == 'n') {
            BST::node *tmp = tree.next(a + 1);
            if (tmp == NULL) cout << "none" << endl;
            else cout << tmp->key << endl;
        } else if (s[0] == 'p') {
            BST::node *tmp = tree.prev(a - 1);
            if (tmp == NULL) cout << "none" << endl;
            else cout << tmp->key << endl;
        }
    }
    return 0;
}
