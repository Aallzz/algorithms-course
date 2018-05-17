#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)3e5 + 10;
const long long inf = (long long)1e18 + 10;
 
 
#define taskname "rmq"
#define taski taskname".in"
#define tasko taskname".out"
 
#ifndef Alex_PKZDL
#define file ifstream cin(taski); ofstream cout(tasko)
//#define file freopen(taski, "r", stdin); freopen(tasko, "w", stdout)
#else
//#define file ifstream cin("input.txt"); ofstream cout("output.txt")
#define file freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout)
#endif
 
struct Heap{
    long long a[N];
    int sz, link[N], id[N];
 
    void siftUp(int i){
        while (a[i] < a[(i - 1) / 2]){
            swap(a[i], a[(i - 1) / 2]);
            swap(id[i], id[(i - 1) / 2]);
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
            i = cur;
        }
    }
 
    void push(long long x, int idx){
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
 
    void decreaseKey(int x, long long d){
        a[link[x]] = d;
        siftUp(link[x]);
        siftDown(link[x]);
    }
 
    long long getMin(){
        return (sz >= 1?  a[0] : -inf);
    }
};
 
vector<pair<int, pair<int, long long> > > e;
Heap h;
 
long long n, m, ans[N];
 
int main()
{
    file;
    ios_base::sync_with_stdio(false);
 
    cin >> n >> m;
 
    for (int i = 1; i <= m; ++i){
        int a, b, x; cin >> a >> b >> x; a--; b--;
        e.push_back(make_pair(a, make_pair(-i, x)));
        e.push_back(make_pair(b, make_pair(i, x)));
    }
 
    for (int i = 0; i < n; ++i) ans[i] = -inf;
    sort(e.begin(), e.end());
 
    int pp = 0;
 
    for (int i = 0; i < (int)e.size(); ++i){
 
        int p = e[i].first;
        int tp = e[i].second.first;
        long long x = e[i].second.second;
 
        while (pp < p){
            if (ans[pp] == -inf) ans[pp] = -h.getMin();
            pp++;
        }
 
        if (tp < 0){
            h.push(-x, -tp);
        } else {
            if (ans[p] == -inf) ans[p] = -h.getMin();
            h.decreaseKey(tp, -inf);
            h.extractMin();
        }
    }
 
    for (int i = 0; i < n; ++i) {
        ans[i] = max(ans[i], -(1LL << 31LL));
        ans[i] = min(ans[i], (1LL << 31LL) - 1);
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
