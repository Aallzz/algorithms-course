#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)2e5 + 10;
 
 
#define taskname "dsu"
#define taski taskname".in"
#define tasko taskname".out"
 
#ifndef Alex_PKZDL
#define file ifstream cin(taski); ofstream cout(tasko)
//#define file freopen(taski, "r", stdin); freopen(tasko, "w", stdout)
#else
//#define file ifstream cin("input.txt"); ofstream cout("output.txt")
#define file freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#endif
 
int n, m, shift;
 
struct DSU
{
    int parent[N], rang[N], len[N];
 
    void makeSets(){
        for (int i = 0; i < n; ++i){
            parent[i] = i;
            rang[i] = len[i] = 0;
        }
    }
 
    pair<int, int> findSetPair(int v){
        if (parent[v] == v) return make_pair(v, len[v]);
        pair<int, int> res = findSetPair(parent[v]);
        len[v] = (len[v] + res.second + 1 - (rang[parent[v]] != 0)) % 2;
        parent[v] = res.first;
        return make_pair(parent[v], len[v]);
    }
 
    int findSet(int v){
        return findSetPair(v).first;
    }
 
    void unionSets(int a, int b){
 
        int ln1 = findSetPair(a).second;
        int ln2 = findSetPair(b).second;
 
        a = findSet(a);
        b = findSet(b);
 
        if (a != b){
            if (rang[a] < rang[b]) swap(a, b), swap(ln1, ln2);
            parent[b] = a;
            if (rang[a] == rang[b]) rang[a]++;
            len[b] += ln1 + ln2 + 1;
        }
    }
 
    bool HaveTheSameColor(int a, int b){
 
        return (findSetPair(a).second + findSetPair(b).second) % 2 == 0;
    }
};
 
DSU dsu;
 
int main()
{
    #ifdef Alex_PKZDL
    file;
    #endif // Alex_PKZDL
 
    ios_base::sync_with_stdio(false);
 
    cin >> n >> m;
    dsu.makeSets();
    for (int i = 0; i < m; ++i){
        int tp, a, b;
        cin >> tp >> a >> b; a--; b--;
        if (tp == 0){
            int x = (a + shift) % n;
            int y = (b + shift) % n;
            dsu.unionSets(x, y);
        } else {
            int x = (a + shift) % n;
            int y = (b + shift) % n;
            bool res = dsu.HaveTheSameColor(x, y);
            if (res){
                cout << "YES" << endl;
                (shift += 1) %= n;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
