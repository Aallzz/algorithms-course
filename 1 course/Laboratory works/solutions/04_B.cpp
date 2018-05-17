#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "lis"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)3e5 + 10;
const int inf = (int)1e9 + 10;
 
int d[N];
int a[N], n, ps[N], prv[N];
int main()
{
    ios_base::sync_with_stdio(false);
 
    #ifndef Alex_PKZDL
        ifstream cin(taski);
        ofstream cout(tasko);
    #else
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #endif // Alex_PKZDL
 
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
 
    for (int i = 0; i <= n; ++i) d[i] = (i ? inf : -inf), ps[i] = -1;
 
    for (int i = 0; i < n; ++i) {
        int j = (int)(upper_bound(d, d + n, a[i]) - d);
        if (d[j - 1] < a[i] && a[i] < d[j]){
            d[j] = a[i];
            ps[j] = i;
            prv[i] = ps[j - 1];
        }
    }
 
    int v = 0;
    for (int i = 0; i <= n; ++i)
        if (ps[i] != -1) v = i;
 
    cout << v << endl;
    vector<int> ans;
    int cur = ps[v];
    while (cur != -1){
        ans.push_back(a[cur]);
        cur = prv[cur];
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) cout << ans[i] << " ";
    cout << endl;
    return 0;
}
