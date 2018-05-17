#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "map"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = 1003273;
constexpr int P = 51;
constexpr int mod = N;
const string none = "none";
 
vector<pair<string, string> > hs[N + 100];
 
int get_hash(string s) {
    int cur_hash = 0;
    for (int i = 0; i < (int)s.length(); ++i) {
        cur_hash = (cur_hash * P + s[i] - 'a' + mod) % mod;
    }
    return cur_hash;
}
 
void put(string x, string y) {
    int cur_hs = get_hash(x);
    for (auto &cur : hs[cur_hs]) {
        if (cur.first == x) {
            cur.second = y;
            return ;
        }
    }
    hs[cur_hs].push_back(make_pair(x, y));
}
 
string const* get(string x) {
    int cur_hs = get_hash(x);
    for (auto& cur : hs[cur_hs]) {
        if (cur.first == x) return &cur.second;
    }
    return &none;
}
 
void del(string x) {
    int cur_hs = get_hash(x);
    for (auto cur = hs[cur_hs].begin(); cur != hs[cur_hs].end(); ++cur) {
        if (cur->first == x) {
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
            case 'p' : cin >> y; put(x, y); break;
            case 'g' : cout << *get(x) << endl; break;
            case 'd' : del(x); break;
        }
    }
    return 0;
}
