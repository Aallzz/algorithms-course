#include <bits/stdc++.h>
 
using namespace std;
 
const long long N = (long long)2e5 + 10;
 
 
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
 
 
struct PersistentStack{
    long long stck[N], prev[N], cur = 0, sz = 1, link[N];
 
    void push(long long x, long long id){
        stck[sz++] = x + stck[cur];
        prev[sz - 1] = cur;
        link[id] = sz - 1;
        cur = sz - 1;
    }
 
    void backward(){
        cur = prev[cur];
    }
 
    long long getSum(long long p){
        return stck[link[p]];
    }
 
    void updateCur(long long p){
        cur = link[p];
    }
 
    void makeLink(long long p){
        link[p] = cur;
    }
 
    long long getSumCur(){
        return stck[cur];
    }
};
 
PersistentStack s;
long long n, ans;
 
int main()
{
    #ifdef Alex_PKZDL
    file;
    #endif // Alex_PKZDL
 
    ios_base::sync_with_stdio(false);
 
    cin >> n;
 
    for (long long i = 0; i < n; ++i){
        long long t, x; cin >> t >> x;
        if (x == 0) {
            s.updateCur(t);
            s.backward();
            s.makeLink(i + 1);
        } else {
            s.updateCur(t);
            s.push(x, i + 1);
        }
        ans += s.getSumCur();
    }
    cout << ans << endl;
    return 0;
}
