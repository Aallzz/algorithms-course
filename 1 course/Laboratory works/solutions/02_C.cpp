#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)3e6 + 10;
 
#define taskname "priorityqueue"
#define taski taskname".in"
#define tasko taskname".out"
 
#ifndef Alex_PKZDL
//#define file ifstream cin(taski); ofstream cout(tasko)
#define file freopen(taski, "r", stdin); freopen(tasko, "w", stdout)
#else
//#define file ifstream cin("input.txt"); ofstream cout("output.txt")
#define file freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#endif
 
struct Heap{
    int a[N], sz, link[N], id[N];
 
    void siftUp(int i){
        while (a[i] < a[(i - 1) / 2]){
            swap(a[i], a[(i - 1) / 2]);
            swap(id[i], id[(i - 1) / 2]);
 
//            swap(link[i], link[(i - 1) / 2]);
            link[id[i]] = i;
            link[id[(i - 1) / 2]] = (i - 1) / 2;
            i = (i - 1) / 2;
        }
    }
 
    void siftDown(int i){
        while (i + i + 1 < sz){
            int lft = i + i + 1;
            int rgh = i + i + 2;
            int cur;
            if (rgh < sz && a[rgh] < a[lft]) cur = rgh;
            else cur = lft;
            if (a[i] <= a[cur]) break;
            swap(a[i], a[cur]);
            swap(id[i], id[cur]);
            link[id[i]] = i;
            link[id[cur]] = cur;
//            swap(link[i], link[cur]);
            i = cur;
        }
    }
 
    void push(int x, int idx){
        a[sz++] = x;
        link[idx] = sz - 1;
        id[sz - 1] = idx;
        siftUp(sz - 1);
    }
 
    void extractMin(){
        if (sz == 0) return ;
        a[0] = a[sz - 1];
        id[0] = id[sz - 1];
        link[id[0]] = 0;
        sz--;
        siftDown(0);
    }
 
    void decreaseKey(int x, int d){
        a[link[x]] = d;
        siftUp(link[x]);
        siftDown(link[x]);
    }
 
    int getMin(){
        return (sz >= 1?  a[0] : -1);
    }
};
 
string s;
Heap h;
 
int main()
{
    file;
    ios_base::sync_with_stdio(false);
 
    int idx = 0;
    while (cin >> s){
        if (s[0] == 'p'){
            int x; cin >> x; h.push(x, idx);
        } else if (s[0] == 'e'){
            int res = h.getMin();
            if (res == -1) cout << "*" << endl;
            else cout << res << endl;
            h.extractMin();
        } else {
            int x, d; cin >> x >> d; x--;
            h.decreaseKey(x, d);
        }
        idx++;
    }
 
    return 0;
}
