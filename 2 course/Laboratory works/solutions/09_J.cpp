#include <bits/stdc++.h>
 
using namespace std;
 
constexpr long long inf {(long long)1e16 + 10};
constexpr size_t N {2 * 355555};
 
int n, m;
struct edge {
    int from, to;
    long long weight;
 
    bool operator < (edge const& e) const {
        return weight < e.weight;
    }
};
 
struct Treap {
 
    struct node {
 
        edge e;
        int priority;
        long long add {};
        pair<edge, int> min_value {{},{}};
 
        node *left {};
        node *right {};
 
        node(edge e) : e(e) {
            priority = rand();
            min_value = {e, 0};
        }
    };
 
    node *root {};
 
    void recalc(node* cur) {
        if (!cur) return ;
        push(cur);
        push(cur->left);
        push(cur->right);
        cur->min_value = {cur->e, 0};
        if (cur->left) cur->min_value = min(cur->min_value, pair<edge, int>(cur->left->min_value.first, -1));
        if (cur->right) cur->min_value = min(cur->min_value, pair<edge, int>(cur->right->min_value.first, 1));
    }
 
    void push(node* cur) {
        if (!cur) return ;
        if (!cur->add) return ;
        if (cur->left) cur->left->add += cur->add;
        if (cur->right) cur->right->add += cur->add;
        cur->min_value.first.weight += cur->add;
        cur->e.weight += cur->add;
        cur->add = 0;
    }
 
    void node_merge(node*& cur, node* left, node *right) {
        push(left);
        push(right);
        if (!left || !right) {
            cur = (left ? left : right);
            return ;
        }
        if (left->priority > right->priority) {
            node_merge(left->right, left->right, right);
            cur = left;
        } else {
            node_merge(right->left, left, right->left);
            cur = right;
        }
        recalc(cur);
    }
 
    edge get_min_value(node*& cur) {
        push(cur);
        if (cur->min_value.second == 0) {
            edge ans = cur->min_value.first;
            node* temp = nullptr;
            node_merge(temp, cur->left, cur->right);
            delete cur;
            cur = temp;
            return ans;
        } else if (cur->min_value.second == -1) {
            edge ans = get_min_value(cur->left);
            recalc(cur);
            return ans;
        } else {
            edge ans = get_min_value(cur->right);
            recalc(cur);
            return ans;
        }
    }
 
    Treap() = default;
 
    Treap(int from, int to, long long w) {
        root = new node({from, to, w});
    }
 
    Treap(edge e) {
        root = new node(e);
    }
 
    Treap* merge(Treap* b) {
        if (b && b->root && b->root != root) {
            node_merge(root, root, b->root);
            delete b;
            b = nullptr;
        }
        return this;
    }
 
    edge get_min_edge() {
        return get_min_value(root);
    }
 
    void add_weight(long long d) {
        if (root != nullptr)
            root->add += d;
    }
 
    void node_clear(node* cur) {
        if (!cur) return ;
        node_clear(cur->left);
        node_clear(cur->right);
        delete cur;
        cur = nullptr;
    }
 
    void clear() {
        if (root) {
            node_clear(root);
            root = nullptr;
        }
    }
 
};
 
int parent[N], rang[N], vertex[N];
Treap* tds[N];
Treap* g[N];
 
bool used[N];
int moveto[N];
 
vector<int> gg[N];
 
int find_set(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find_set(parent[v]);
}
 
void union_sets(int a, int b, int v, Treap* t) {
    a = find_set(a);
    b = find_set(b);
    if (rang[a] > rang[b]) swap(a, b);
    parent[b] = a;
    rang[a] = (rang[a] == rang[b]);
    vertex[a] = v;
    tds[a] = t;
}
 
void dfs(int v) {
    used[v] = true;
    for (int to : gg[v]) {
        if (used[to]) continue;
        dfs(to);
    }
}
 
int main() {
 
#ifdef Alex_PKZDL
    ifstream cin(input_file);
    ofstream cout(output_file);
#endif
 
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
 
    for (int i = 0; i < n + n; ++i)
        g[i] = new Treap();
    for (int i = 0; i < m; ++i) {
        int x, y, w; cin >> x >> y >> w; --x; --y;
        g[y]->merge(new Treap(y, x, w));
        gg[x].push_back(y);
    }
 
    dfs(0);
 
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            cout << "NO" << endl;
            return 0;
        }
    }
 
    fill_n(used, n + n, false);
    for (int i = 0; i < n + n; ++i) {
        parent[i] = i;
        rang[i] = 0;
        tds[i] = g[i];
        vertex[i] = i;
    }
 
    long long ans = 0;
    int k = n;
 
    for (int i = 0; i < n; ++i) {
        if (find_set(i) == find_set(0)) continue;
        int v = i;
        used[v] = true;
        while (true) {
            int cur_component = find_set(v);
            edge cur_min = tds[cur_component]->get_min_edge();
            if (find_set(v) == find_set(cur_min.to)) continue;
            tds[cur_component]->add_weight(-cur_min.weight);
            ans += cur_min.weight;
            moveto[vertex[cur_component]] = cur_min.to;
            if (vertex[find_set(cur_min.to)] == 0) break;
            if (!used[cur_min.to]) {
                used[cur_min.to] = true;
                v = cur_min.to;
                continue;
            }
 
 
            //////////////////////////cycle/////////////////////////////
            int super_vertex = k++;
            int to = cur_min.to;
            parent[cur_component] = super_vertex;
            vertex[cur_component] = super_vertex;
            Treap* cur_t = tds[cur_component];
            while (vertex[find_set(to)] != super_vertex) {
                int next = moveto[vertex[find_set(to)]];
                cur_t->merge(tds[find_set(to)]);
                parent[vertex[find_set(to)]] = super_vertex;
                union_sets(v, to, super_vertex, cur_t);
                to = next;
            }
        }
        v = i;
        while (vertex[find_set(v)]) {
            int next = moveto[vertex[find_set(v)]];
            union_sets(v, 0, 0, nullptr);
            v = next;
        }
    }
 
    for (int i = 0; i < k; ++i) {
        if (find_set(i) != find_set(0)) {
            cout << "NO" << " " << i << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
 
    cout << ans << endl;
    return 0;
}
