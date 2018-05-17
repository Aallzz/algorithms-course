#include <bits/stdc++.h>
 
using namespace std;
 
constexpr size_t A {100};
 
struct trie_node {
  int key {-1};
  int to[A];
 
  trie_node() {
    for (size_t i = 0; i < A; ++i) {
      to[i] = 0;
    }
  }
};
 
struct trie {
  vector<trie_node> t;
 
  trie() {
    t.emplace_back();
  }
 
  void add_string(string const& s) {
    int cur = 0;
    for (const char c : s) {
      if (!t[cur].to[c - 'a']) {
        t[cur].to[c - 'a'] = static_cast<int>(t.size());
        t.emplace_back();
      }
      cur = t[cur].to[c - 'a'];
    }
    t[cur].key++;
  }
 
  size_t size() const {
    return t.size();
  }
 
  vector<vector<pair<int, int>>> make_graph() {
    vector<vector<pair<int, int>>> res(t.size());
    for (int i = 0; i < (int)t.size(); ++i) {
      for (int c = 0; c < (int)A; ++c) {
        if (!t[i].to[c]) continue;
        res[i].push_back({t[i].to[c], c});
      }
    }
    return res;
  }
};
 
string s;
trie t;
 
int main() {
  ifstream cin("trie.in");
  ofstream cout("trie.out");
  cin >> s;
  for (size_t i = 0; i < s.length(); ++i) {
    t.add_string(s.substr(i));
  }
  auto const g = t.make_graph();
  cout << g.size() << " " << g.size() - 1 << endl;
  for (int i = 0; i < (int)g.size(); ++i) {
    for (auto const e : g[i]) {
      cout << i + 1 << " " <<  e.first + 1 << " " << char(e.second + 'a') << "\n";
    }
  }
  return 0;
}
