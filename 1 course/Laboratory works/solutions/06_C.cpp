#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "linkedmap"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = 1003273;
constexpr int P = 51;
constexpr int mod = N;
string none = "none";
 
struct node {
    string key;
    string value;
    node *nxt, *prv;
 
    node(string key, string value, node* prv, node* nxt) :
        key(key), value(value), nxt(nxt), prv(prv) {};
};
 
list<node> hs[N + 100];
node *last;
 
int get_hash(string s) {
    int cur_hash = 0;
    for (int i = 0; i < (int)s.length(); ++i) {
        cur_hash = (cur_hash * P + s[i] - 'a' + mod) % mod;
    }
    return cur_hash;
}
 
void put(string const& x, string const& y) {
    int cur_hs = get_hash(x);
    for (auto cur = hs[cur_hs].begin(); cur != hs[cur_hs].end(); ++cur) {
        if (cur->key == x) {
            cur->value = y;
            return ;
        }
    }
    hs[cur_hs].push_back(node(x, y, last, nullptr));
    if (last) last->nxt = &(hs[cur_hs].back());
    last = &(hs[cur_hs].back());
}
 
string const* get(string const& x) {
    int cur_hs = get_hash(x);
    for (auto& cur : hs[cur_hs]) {
        if (cur.key == x) return &cur.value;
    }
    return &none;
}
 
string const* prev(string const& x) {
    int cur_hs = get_hash(x);
    for (auto& cur : hs[cur_hs]) {
        if (cur.key == x) return (cur.prv ? &((cur.prv)->value) : &none);
    }
    return &none;
}
 
string const* next(string const& x) {
    int cur_hs = get_hash(x);
    for (auto& cur : hs[cur_hs]) {
        if (cur.key == x) return (cur.nxt ? &((cur.nxt)->value) : &none);
    }
    return &none;
}
 
void del(string const& x) {
    int cur_hs = get_hash(x);
    for (auto cur = hs[cur_hs].begin(); cur != hs[cur_hs].end(); ++cur) {
        if (cur->key == x) {
            if (cur->prv) cur->prv->nxt = cur->nxt;
            if (cur->nxt) cur->nxt->prv = cur->prv;
            if (last == &(*cur))
                last = cur->prv;
            hs[cur_hs].erase(cur);
            return ;
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
 
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    string type;
    string x, y;
 
    while (cin >> type >> x) {
        switch (type[0]) {
            case 'p' : switch (type[1]) {
                        case 'u' : cin >> y; put(x, y); break;
                        case 'r' : cout << *prev(x) << endl; break;
                       }; break;
            case 'g' : cout << *get(x) << endl; break;
            case 'd' : del(x); break;
            case 'n' : cout << *next(x) << endl; break;
        }
    }
    return 0;
}
