#include <bits/stdc++.h>
 
using namespace std;
 
//#define std_input_output
 
#ifndef std_input_output
    #define taskname "codelock"
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr size_t K {23};
constexpr size_t D {13};
constexpr size_t N {1666666};
 
int key[K];
int k, d;
 
bool add_key() {
    for (int i = 0; i <= k; ++i) {
        key[i] += 1;
        if (key[i] >= d) {
            key[i] = 0;
            continue;
        }
        break;
    }
    return key[k] != 1;
}
 
vector<string> q;
map<string, int> mp;
vector<int> g[N];
 
string get_string_key() {
    string res;
    for (int i = 0; i < k; ++i) {
        res += to_string(key[i]);
    }
    return res;
}
 
vector<int> path;
set<pair<int, int>> was;
 
int main() {
 
#ifdef HOME
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);
#else
    #ifndef std_input_output
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif
#endif
 
    ios_base::sync_with_stdio(false);
 
    cin >> d >> k;
    k--;
    if (k == 0) {
        for (int i = 0; i < d; ++i) {
            cout << i;
        }
        return 0;
    }
    do {
        mp[get_string_key()] = (int)q.size();
        q.push_back(get_string_key());
    } while (add_key());
 
    for (int i = 0; i < (int)q.size(); ++i) {
        for (int lst = 0; lst < d; ++lst) {
            int to = mp[q[i].substr(1, q[i].length() - 1) + char('0' + lst)];
                g[i].push_back(to);
        }
    }
    ++k;
    vector<int> st;
    st.push_back(0);
    while (!st.empty()) {
        int v = st.back();
 
        if (g[v].size() == 0) {
            path.push_back(v);
            st.pop_back();
            continue;
        }
 
        int to = g[v].back();
        g[v].pop_back();
 
        while (g[v].size() != 0 && (was.count({v, to}))) {
            to = g[v].back();
            g[v].pop_back();
        }
        if (was.count({v, to})) {
            path.push_back(v);
            st.pop_back();
        } else {
            st.push_back(to);
            was.insert({v, to});
        }
    }
 
 
    string ans = q[path[path.size() - 1]];
 
    for (int i = (int)path.size() - 2; i >= 0; --i) {
        ans += q[path[i]].back();
    }
    cout << ans << endl;
    cout << endl;
    return 0;
}
