#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)2e5 + 10;
 
#define taskname "restructure"
#define taski taskname".in"
#define tasko taskname".out"
 
#ifndef Alex_PKZDL
#define file ifstream cin(taski); ofstream cout(tasko)
//#define file freopen(taski, "r", stdin); freopen(tasko, "w", stdout)
#else
//#define file ifstream cin("input.txt"); ofstream cout("output.txt")
#define file freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#endif
 
int s[N], n, q;
 
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
 
DSU dsu1, dsu2;
int main()
{
    file;
    ios_base::sync_with_stdio(false);
 
    cin >> n >> q;
 
    dsu1.makeSets();
    dsu2.makeSets();
 
    while (q--){
        int tp; cin >> tp;
        if (tp == 1){
            int a, b; cin >> a >> b; a--; b--;
            dsu1.unionSets(a, b);
        } else if (tp == 2){
            int a, b; cin >> a >> b; a--; b--;
            while (dsu2.getNxt(a) + 1 <= b){
                int nextA = dsu2.getNxt(a) + 1;
                dsu1.unionSets(a, nextA);
                dsu2.unionSets(a, nextA);
                a = nextA;
            }
        } else {
            int a, b; cin >> a >> b; a--; b--;
            if (dsu1.InOneSet(dsu2.findSet(a), dsu2.findSet(b)) || dsu2.InOneSet(dsu1.findSet(a), dsu1.findSet(b)) ||
                dsu1.InOneSet(a, b) || dsu2.InOneSet(a, b)) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
    return 0;
}
