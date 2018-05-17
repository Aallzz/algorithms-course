#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)3e5 + 10;
 
#define taskname "dsu"
#define taski taskname".in"
#define tasko taskname".out"
 
#ifndef Alex_PKZDL
//#define file ifstream cin(taski); ofstream cout(tasko)
#define file freopen(taski, "r", stdin); freopen(tasko, "w", stdout)
#else
//#define file ifstream cin("input.txt"); ofstream cout("output.txt")
#define file freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#endif
 
int parent[N], mx[N], mn[N], sz[N];
int n;
 
void makeSets(){
    for (int i = 0; i < n; ++i){
        parent[i] = mx[i] = mn[i] = i;
        sz[i] = 1;
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
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        mx[a] = max(mx[a], mx[b]);
        mn[a] = min(mn[a], mn[b]);
        sz[a] += sz[b];
    }
}
 
void getMinMaxCntSet(int a){
    a = findSet(a);
    cout << mn[a] + 1 << " " << mx[a] + 1 << " " << sz[a] << endl;
}
 
int main()
{
    file;
    ios_base::sync_with_stdio(false);
 
    cin >> n;
    cerr << n << endl;
    makeSets();
    string s;
    while (cin >> s){
        int a, b;
        if (s[0] == 'u'){
            cin >> a >> b; a--; b--;
            unionSets(a, b);
        } else {
            cin >> a; a--;
            getMinMaxCntSet(a);
        }
    }
    return 0;
}
