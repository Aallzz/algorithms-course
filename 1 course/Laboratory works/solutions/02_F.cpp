#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)2e5 + 10;
 
#define taskname "cutting"
#define taski taskname".in"
#define tasko taskname".out"
 
#ifndef Alex_PKZDL
#define file ifstream cin(taski); ofstream cout(tasko)
//#define file freopen(taski, "r", stdin); freopen(tasko, "w", stdout)
#else
//#define file ifstream cin("input.txt"); ofstream cout("output.txt")
#define file freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#endif
 
int n, q, m;
 
struct DSU{
    int parent[N], rang[N], nxt[N];
 
    void makeSets(){
        for (int i = 0; i < n + 1; ++i){
            parent[i] = i;
            rang[i] = 0;
            nxt[i] = i;
        }
    }
 
    int findSet(int v){
        if (parent[v] == v) return v;
        return parent[v] = findSet(parent[v]);
    }
 
    void unionSets(int a, int b){
        a = findSet(a);
        b = findSet(b);
        if (a != b){
            if (rang[a] < rang[b]) swap(a, b);
            parent[b] = a;
            nxt[a] = max(nxt[a], nxt[b]);
            if (rang[a] == rang[b]) rang[a]++;
        }
    }
 
    int getNxt(int a){
        a = findSet(a);
        return nxt[a];
    }
 
    bool InOneSet(int a, int b){
        return findSet(a) == findSet(b);
    }
};
 
DSU dsu;
vector<pair<int, pair<int, int> > > query;
vector<int> ans;
 
int main()
{
    file;
    ios_base::sync_with_stdio(false);
 
    cin >> n >> m >> q;
    for (int i = 0; i < m; ++i){
        int x, y; cin >> x >> y;
    }
 
    for (int i = 0; i < q; ++i){
        string s; int a, b; cin >> s >> a >> b; a--; b--;
        if (s[0] == 'a'){
            query.push_back(make_pair(0, make_pair(a, b)));
        } else {
            query.push_back(make_pair(1, make_pair(a, b)));
        }
    }
 
    dsu.makeSets();
 
    for (int i = q - 1; i >= 0; --i){
        int tp = query[i].first;
        int a = query[i].second.first;
        int b = query[i].second.second;
 
        if (tp == 0){
            ans.push_back(dsu.InOneSet(a, b));
        } else {
            dsu.unionSets(a, b);
        }
    }
 
    reverse(ans.begin(), ans.end());
 
    for (int i = 0; i < (int)ans.size(); ++i) cout << (ans[i] == 0 ? "NO" : "YES") << endl;
    return 0;
}
