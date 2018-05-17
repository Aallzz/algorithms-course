#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)3e5 + 10;
 
pair<pair<int, int>, int> a[N];
pair<int, pair<int, int> > ans[N];
 
int n;
 
map<int, int> mp;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x, y; cin >> x >> y;
        a[i] = make_pair(make_pair(x, y), i);
    }
 
    sort(a + 1, a + n + 1, [](pair<pair<int, int>, int> x, pair<pair<int, int>,int> y)->bool{return x.first.first < y.first.first;});
    for (int i = 1; i <= n; ++i) {
        mp[a[i].second] = i;
    }
 
    int cur = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i].first.second > a[cur].first.second) {
            ans[cur].second.second = a[i].second;
            ans[i].first = a[cur].second;
        } else {
            int anc = (ans[cur].first != 0 ? mp[ans[cur].first] : 0);
            while (a[anc].first.second > a[i].first.second && anc != 0) {
                cur = anc;
                anc = (ans[cur].first != 0 ? mp[ans[cur].first] : 0);
            }
 
            if (anc == 0) {
                ans[i].second.first = a[cur].second;
                ans[cur].first = a[i].second;
            } else {
                ans[anc].second.second = a[i].second;
                ans[i].first = a[anc].second;
                ans[i].second.first = a[cur].second;
                ans[cur].first = a[i].second;
            }
 
        }
        cur = i;
    }
 
    cout << "YES" << endl;
    for (map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
        int i = it->second;
        if (i == 0) continue;
        cout << ans[i].first << " " << ans[i].second.first << " " << ans[i].second.second << endl;
    }
 
    return 0;
}
