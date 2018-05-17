#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "knapsack"
#define taski taskname".in"
#define tasko taskname".out"
 
const int M = (int)1e4 + 10;
const int N = (int)1e3 + 10;
const int inf = (int)1e9 + 10;
 
int bp[N][M];
int prv[N][M];
 
int w[N], c[N], n, m, cur;
 
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
 
 
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i <= n; ++i) cin >> c[i];
 
    for (int i = 1; i <= n; ++i){
        for (int j = m; j >= 0; --j){
            bp[i][j] = bp[i - 1][j];
            prv[i][j] = 0;
            if (j - w[i] == 0 || (j - w[i] >= 0 && bp[i - 1][j - w[i]] != 0)){
               if (bp[i][j] < bp[i - 1][j - w[i]] + c[i]){
                    bp[i][j] = bp[i - 1][j - w[i]] + c[i];
                    prv[i][j] = i;
               }
            }
        }
    }
 
    int v = 0;
    for (int i = 0; i <= m; ++i)
        if (bp[n][i] > bp[n][v]) v = i;
 
    vector<int> ans;
 
    for (int i = n; i >= 0; --i){
        int id = prv[i][v];
        if (id != 0) ans.push_back(id);
        if (id != 0) v = v - w[id];
    }
 
    cout << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) cout << ans[i] << " ";
    cout << endl;
    return 0;
}
