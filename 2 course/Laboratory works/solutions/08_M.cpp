#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "tiv"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t A {27};
 
vector<int> g[A];
vector<string> s;
size_t n;
 
vector<int> sorted;
vector<pair<int, int>> ans;
int used[A];
 
bool dfs(int v) {
    used[v] = 1;
    for (int& to : g[v]) {
        if (used[to] == 1) return false;
        if (used[to] == 2) continue;
        if (!dfs(to)) return false;
    }
    used[v] = 2;
    sorted.push_back(v);
    return true;
}
 
 
int main() {
    ios_base::sync_with_stdio(false);
 
#ifdef Alex_PKZDL
    ifstream cin(input_file);
    ofstream cout(output_file);
#else
    ifstream cin(taski);
    ofstream cout(tasko);
#endif
 
    cin >> n;
    s.resize(n);
 
    for (string& cur : s) {
        cin >> cur;
        if (cur.length() > 1) {
            g[0].push_back(cur[0] - 'a' + 1);
        }
    }
 
    for (size_t i = 1; i != n; ++i) {
        string& cur = s[i];
        string& prv = s[i - 1];
        if (prv.length() > cur.length() || cur == prv) {
            cout << "No" << endl;
            return 0;
        }
        if (prv.length() != cur.length()) continue;
 
        for (size_t pos = 0; pos < cur.length(); ++pos) {
            if (cur[pos] == prv[pos]) continue;
            g[prv[pos] - 'a' + 1].push_back(cur[pos] - 'a' + 1);
            break;
        }
    }
 
    bool acyclic = true;
    for (size_t i = 0; i != A; ++i) {
        if (used[i]) continue;
        acyclic &= dfs(i);
    }
 
    if (!acyclic) {
        cout << "No" << endl;
        return 0;
    }
 
    reverse(sorted.begin(), sorted.end());
    ans.resize(A);
    for(size_t i = 0; i < A; ++i)
        ans[i] = {sorted[i], i};
 
    sort(ans.begin(), ans.end());
 
    for_each(ans.begin(), ans.end(),
             [](pair<int, int>& x){
                if (x != ans[0] && x.second >= ans[0].second) x.second--;
            });
 
    if (ans[0].second == 0) {
        cout << "No" << endl;
        return 0;
    }
 
    cout << "Yes" << endl;
    for (size_t i = 1; i < ans.size(); ++i) {
        cout << ans[i].second << " ";
    }
    cout << endl;
    return 0;
}
