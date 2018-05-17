#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)3e6 + 10;
 
#define taskname "parking"
#define taski taskname".in"
#define tasko taskname".out"
 
#ifndef Alex_PKZDL
//#define file ifstream cin(taski); ofstream cout(tasko)
#define file freopen(taski, "r", stdin); freopen(tasko, "w", stdout)
#else
//#define file ifstream cin("input.txt"); ofstream cout("output.txt")
#define file freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#endif
 
int parent[N], rang[N], mx[N];
int n;
 
void makeSets(){
    for (int i = 0; i < n + 1; ++i){
        parent[i] = i;
        rang[i] = 0;
        mx[i] = i;
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
        mx[a] = max(mx[a], mx[b]);
        if (rang[a] == rang[b]) rang[a]++;
    }
}
 
int getMx(int a){
    a = findSet(a);
    return mx[a];
}
 
int main()
{
    file;
    ios_base::sync_with_stdio(false);
 
    cin >> n;
    makeSets();
    for (int i = 0; i < n; ++i){
        int x; cin >> x; x--;
        int v = getMx(x);
        if (v < n){
            unionSets(v + 1, v);
            cout << v + 1 << endl;
        } else {
            v = getMx(0);
            unionSets(v + 1, v);
            cout << v + 1 << endl;
        }
    }
    return 0;
}
