#include <bits/stdc++.h>
 
using namespace std;
 
class SplayTree {
 
public:
 
    struct node {
        long long key;
        node *left, *right;
 
        node(long long key) : key(key) {
            left = right = NULL;
        }
 
        node() {};
    };
 
 
private:
 
    node *root;
 
    node* leftRotate(node *&cur) {
        node *tmp = cur->right;
        cur->right = tmp->left;
        tmp->left = cur;
        return tmp;
    }
 
    node* rightRotate(node *cur) {
        node *tmp = cur->left;
        cur->left = tmp->right;
        tmp->right = cur;
        return tmp;
    }
 
 
    node* splay(node *cur, long long k) {
        if (cur == NULL) return NULL;
 
        if (k < cur->key) {
            if (cur->left == NULL) return cur;
 
            if (k < cur->left->key) {
                cur->left->left = splay(cur->left->left, k);
                cur = rightRotate(cur);
            } else if (k > cur->left->key) {
                cur->left->right = splay(cur->left->right, k);
                if (cur->left->right != NULL)
                    cur->left = leftRotate(cur->left);
            }
            return (cur->left == NULL ? cur : rightRotate(cur));
        } else if (k > cur->key) {
            if (cur->right == NULL) return cur;
 
            if (k < cur->right->key) {
                cur->right->left = splay(cur->right->left, k);
                if (cur->right->left != NULL)
                    cur->right = rightRotate(cur->right);
            } else if (k > cur->right->key) {
                cur->right->right = splay(cur->right->right, k);
                cur = leftRotate(cur);
            }
            return (cur->right == NULL ? cur : leftRotate(cur));
        } else {
            return cur;
        }
    }
 
 
    node* maximum(node *cur) {
        if (cur == NULL) return NULL;
        if (cur->right == NULL) return cur;
        return maximum(cur->right);
    }
 
    node* minimum(node *cur) {
        if (cur == NULL) return NULL;
        if (cur->left == NULL) return cur;
        return minimum(cur->left);
    }
 
public:
 
    SplayTree() {}
 
    void put(long long k) {
        if (root == NULL) {
            root = new node(k);
            return ;
        }
        root = splay(root, k);
        if (k < root->key) {
            node *tmp = new node(k);
            tmp->left = root->left;
            tmp->right = root;
            root->left = NULL;
            root = tmp;
        } else if (k > root->key) {
            node *tmp = new node(k);
            tmp->right = root->right;
            tmp->left = root;
            root->right = NULL;
            root = tmp;
        }
    }
 
    bool contains(long long k) {
        root = splay(root, k);
        if (root == NULL) return false;
        return root->key == k;
    }
 
    void del(long long k) {
        if (root == NULL) return ;
 
        root = splay(root, k);
 
        if (root->key == k) {
            if (root->left == NULL) {
                node* tmp = root;
                root = root->right;
                delete tmp;
            }
            else {
                node *tmp = root;
                root = splay(root->left, k);
                root->right = tmp->right;
                delete tmp;
            }
        }
    }
 
    node* prev(long long k) {
        if (root == NULL) return NULL;
        root = splay(root, k);
        if (root->key != k) {
            put(k);
            node *res = maximum(root->left);
            del(k);
            return res;
        }
        node *res = maximum(root->left);
        return res;
    }
 
    node* next(long long k) {
        if (root == NULL) return NULL;
        root = splay(root, k);
        if (root->key != k) {
            put(k);
            node *res = minimum(root->right);
            del(k);
            return res;
        }
        node *res = minimum(root->right);
        return res;
    }
 
};
 
SplayTree tree;
 
int main() {
    string s;
    long long a;
    while (cin >> s >> a) {
        if (s[0] == 'i') {
            tree.put(a);
        } else if (s[0] == 'd') {
            tree.del(a);
        } else if (s[0] == 'e') {
            cout << (tree.contains(a) ? "true" : "false") << endl;
        } else if (s[0] == 'n') {
            SplayTree::node *tmp = tree.next(a);
            if (tmp == NULL) cout << "none" << endl;
            else cout << tmp->key << endl;
        } else if (s[0] == 'p') {
            SplayTree::node *tmp = tree.prev(a);
            if (tmp == NULL) cout << "none" << endl;
            else cout << tmp->key << endl;
        }
    }
    return 0;
}
