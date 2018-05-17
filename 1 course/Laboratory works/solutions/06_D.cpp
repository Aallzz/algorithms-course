#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "multimap"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = 10373;
constexpr int M = 781;
constexpr int P = 31;
constexpr int mod_1 = N;
constexpr int mod_2 = M;
 
list<string> none = list<string>{};
 
list<pair<string, string>> hs[N + 100][M];
 
pair<int, int> c[N];
 
int get_hash(string const& s, int mod) {
    int cur_hash = 0;
    for (int i = 0; i < (int)s.length(); ++i) {
        cur_hash = (cur_hash * P + s[i] - 'a' + mod) % mod;
    }
    return cur_hash;
}
 
void put(string const& x, string const& y) {
    int cur_hs1 = get_hash(x, mod_1);
    int cur_hs2 = get_hash(y, mod_2);
    for (auto cur = hs[cur_hs1][cur_hs2].begin(); cur != hs[cur_hs1][cur_hs2].end(); ++cur) {
        if (cur->first == x && cur->second == y) {
            return ;
        }
    }
    hs[cur_hs1][cur_hs2].push_back(pair<string, string>{x, y});
}
 
list<string> get(string const& x) {
    int cur_hs1 = get_hash(x, mod_1);
    list<string> res;
 
    for (int i = 0; i < M; ++i) {
        for (auto p = hs[cur_hs1][i].begin(); p != hs[cur_hs1][i].end(); ++p) {
            if (p->first == x) res.push_back(p->second);
        }
    }
 
    if (res.size())
        return res;
    return none;
}
 
void delete_single(string const& x, string const& y) {
    int cur_hs1 = get_hash(x, mod_1);
    int cur_hs2 = get_hash(y, mod_2);
 
    for (auto cur = hs[cur_hs1][cur_hs2].begin(); cur != hs[cur_hs1][cur_hs2].end(); ++cur) {
        if (cur->first == x && cur->second == y) {
            hs[cur_hs1][cur_hs2].erase(cur);
            return ;
        }
    }
}
 
void delete_all(string const& x) {
    int cur_hs1 = get_hash(x, mod_1);
    for (int i = 0; i < M; ++i) {
        hs[cur_hs1][i].clear();
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
            case 'p' : case 'u' : cin >> y; put(x, y); break;
            case 'g' : {
                           auto res = get(x);
                           cout << res.size() << " ";
                           for (auto c : res) cout << c << " ";
                           cout << endl;
                           break;
                       }
            case 'd' : switch (type.length()) {
                           case 6 : cin >> y; delete_single(x, y); break;
                           default : delete_all(x); break;
                       }
        }
    }
    return 0;
}
