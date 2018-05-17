#include <bits/stdc++.h>
 
using namespace std;
 
#define std_input_output
#ifndef std_input_output
    #define taskname "tree"
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr size_t A {100};
constexpr char mn_char {static_cast<char>('a' - 1)};
 
struct hash_struct {
 
    // s[0]
    // s[0] * p + s[1]
    // s[0] * p^2 + s[1] * p + s[2]
    // s[0] * p^3 + s[1] * p^2 + s[2] * p + s[3]
    // s[0] * p^4 + s[1] * p^3 + s[2] * p^2 + s[3] * p + s[4]
    //
    // s[1] * p^2 + s[2] * p + s[3]
    //
 
  static constexpr long long mod {1000000007};
  static constexpr long long p {253};
 
  string str;
  vector<long long> hsh;
  vector<long long> pw;
 
  explicit hash_struct(string s)
    : str(std::move(s)) {
    int n = static_cast<int>(str.length());
    hsh.resize(n);
    pw.resize(n + 1);
    pw[0] = 1ll;
    hsh[0] = str[0] - mn_char;
    for (int i = 1; i < n; ++i) {
      hsh[i] = (hsh[i - 1] * p + str[i] - mn_char) % mod;
      pw[i] = (pw[i - 1] * p) % mod;
    }
    pw[n] = (pw[n - 1] * p) % mod;
  }
 
  long long get_hash(int l, int r) const {
    assert(l < r);
    assert(0 <= l);
    assert(r <= (int)str.length());
    auto h = (hsh[r - 1] - ((l == 0 ? 0 : hsh[l - 1]) * pw[r - l]) % mod + mod) % mod;
    return h;
  }
 
  long long equal(int l, int r, int ll, int rr) const {
    return get_hash(l, r) == get_hash(ll, rr);
  }
 
  string const& get_string() const {
    return str;
  }
 
  int find_common_prefix_len(int pos1_start, int pos1_end, int pos2_start, int pos2_end) const {
    int l = 0;
    int r = min(pos1_end - pos1_start, pos2_end - pos2_start);
    while (r - l > 1) {
      int mid = (l + r) / 2;
      long long hsh1 = get_hash(pos1_start, pos1_start + mid);
      long long hsh2 = get_hash(pos2_start, pos2_start + mid);
      if (hsh1 == hsh2) {
        l = mid;
      } else {
        r = mid;
      }
    }
    if (get_hash(pos1_start, pos1_start + r) == get_hash(pos2_start, pos2_start + r)) l = r;
    return l;
  }
 
  int get_min_start(int l, int ) const {
//      auto h = get_hash(l, r);
      return l;
  }
};
 
struct trie_node;
 
struct trie_node {
  int l {-1};
  int r {-1};
  int id {0};
  trie_node *to[A];
 
  trie_node() {
    for (int i = 0; i < (int)A; ++i) {
      to[i] = nullptr;
    }
  }
 
  trie_node(int ll, int rr) : trie_node() {
    l = ll;
    r = rr;
  }
};
 
struct trie {
  trie_node *root;
  int sz;
 
  trie() {
    root = new trie_node();
    sz = 1;
  }
 
  void add_string(hash_struct const& hs, int l, int r) {
    trie_node *cur = root;
    trie_node *t = cur->to[hs.get_string()[l] - mn_char];
    if (t) {
     label:
     int prefix_len = hs.find_common_prefix_len(t->l, t->r, l, r);
     if (prefix_len == t->r - t->l) {
        l += prefix_len;
//        t = t->to[hs.get_string()[l] - mn_char];
        if (l >= r) return ;
        if (!(t->to[hs.get_string()[l] - mn_char])) {
            t->to[hs.get_string()[l] - mn_char] = new trie_node(l, r);
            t->to[hs.get_string()[l] - mn_char]->id = sz++;
            return ;
        } else {
            t = t->to[hs.get_string()[l] - mn_char];
        }
        goto label;
     }
     if (prefix_len == r - l) return ;
     int ll = hs.get_min_start(t->l + prefix_len, t->r);
     int rr = ll + (t->r - t->l - prefix_len);
 
     trie_node *split_node = new trie_node(ll, rr);
     for (int i = 0; i < (int)A; ++i) {
         split_node->to[i] = t->to[i];
         t->to[i] = nullptr;
     }
 
     ll = hs.get_min_start(t->l, t->l + prefix_len);
     rr = ll + (t->l + prefix_len - t->l);
 
     t->l = ll;
     t->r = rr;
     t->to[hs.get_string()[t->r] - mn_char] = split_node;
     split_node->id = sz++;
 
     if (l + prefix_len < r) {
        ll = hs.get_min_start(l + prefix_len, r);
        rr = ll + (r - l - prefix_len);
        trie_node *new_node = new trie_node(ll, rr);
        t->to[hs.get_string()[ll] - mn_char] = new_node;
        new_node->id = sz++;
     }
    } else {
      cur->to[hs.get_string()[l] - mn_char] = new trie_node(l, r);
      cur->to[hs.get_string()[l] - mn_char]->id = sz++;
    }
  }
 
  int get_vertex(map<int, int>& mp, int& num, int v) const {
      if (!mp.count(v)) {
          mp[v] = num++;
      }
      return mp[v];
  }
 
  mutable map<int, int> mp;
  mutable int num {};
 
  void dfs(hash_struct const& hs, vector<vector<pair<int,pair<int,int>>>>& g, trie_node const * const cur) const {
 
    for (int i = 1; i < (int)A; ++i) {
      if (cur->to[i]) {
        int len = cur->to[i]->r - cur->to[i]->l;
        int start = hs.get_min_start(cur->to[i]->l, cur->to[i]->r);
        int add = 0; //(start + len == (int)hs.get_string().length());
 
        int v = get_vertex(mp, num, cur->id);
        int to = get_vertex(mp, num, cur->to[i]->id);
 
        g[v].push_back({to, {start, start + len - add}});
        dfs(hs, g, cur->to[i]);
      }
    }
  }
 
  auto make_graph(hash_struct const& hs) const {
    vector<vector<pair<int,pair<int,int>>>> g (sz);
    mp.clear();
    num = 0;
    dfs(hs, g, root);
    g.resize(num);
    return g;
  }
 
  void clear(trie_node *cur) {
      if (!cur) return ;
      for (int i = 0; i < (int)A; ++i) {
          clear(cur->to[i]);
      }
      delete cur;
      cur = nullptr;
  }
 
  ~trie() {
      clear(root);
  }
 
};
 
string s;
trie t;
 
int main() {
    #ifdef Alex_PKZDL
        freopen(input_file, "r", stdin);
        freopen(output_file, "w", stdout);
    #else
        #ifndef std_input_output
            freopen(taski, "r", stdin);
            freopen(tasko, "w", stdout);
        #endif
    #endif
    ios_base::sync_with_stdio(false);
 
    cin >> s;
//    s += mn_char;
    hash_struct hs(s);
    for (size_t i = 0; i < s.length(); ++i) {
      t.add_string(hs, (int)i, (int)s.length());
    }
    auto const g = t.make_graph(hs);
    cout << g.size() << " " << g.size() - 1 << endl;
    for (int i = 0; i < (int)g.size(); ++i) {
      for (auto const e : g[i]) {
        cout << i + 1 << " " <<  e.first + 1 << " " << e.second.first + 1 << " " << e.second.second << "\n";
      }
    }
    return 0;
}
