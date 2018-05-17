#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "fastadd"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int n = 1 << 24;
 
unsigned int d[n + 100];
unsigned int a, b;
int q, m;
 
unsigned int cur = 0;
unsigned int add, l, r;
 
inline unsigned int nextRand() {
    cur = cur * a + b;
    return (cur >> 8);
}
 
int main() {
    ios_base::sync_with_stdio(false);
 
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    cin >> m >> q;
    cin >> a >> b;
 
    while (m--) {
        add = nextRand();
        l = nextRand();
        r = nextRand();
        if (l > r) swap(l, r);
        d[l + 1] += add;
        d[r + 2] -= add;
    }
 
    unsigned int sm = 0;
    for (int i = 1; i <= n; ++i) {
        sm += d[i];
        d[i] = sm;
    }
 
    for (int i = 2; i <= n; ++i) {
        d[i] += d[i - 1];
    }
 
    unsigned int res = 0;
 
    while (q--) {
        l = nextRand();
        r = nextRand();
        if (l > r) swap(l, r);
        res += d[r + 1] - d[l];
    }
 
    cout << res << endl;
 
    return 0;
}
