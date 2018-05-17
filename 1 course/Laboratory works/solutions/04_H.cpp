#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "perm"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = 17;
 
int n, m, k, a[N];
long long f[N][(1 << N)];
int gcd[N][N];
int msk;
 
vector<int> ans;
 
void getPermutation(long long num, int lst = -1){
    if (msk == 0) return;
    long long sum = 0LL;
    for (int i = 0; i < n; ++i){
        if (!(msk & (1 << i))) continue;
        if (lst != -1 && gcd[lst][i] < k) continue;
        sum += f[i][msk];
        if (sum >= num) {
            msk ^= (1 << i);
            ans.push_back(a[i]);
            getPermutation(num - (sum - f[i][msk ^ (1 << i)]), i);
        }
    }
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif
 
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
 
    sort(a, a + n);
 
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            gcd[i][j] = __gcd(a[i], a[j]);
 
    f[0][0] = 1;
    msk = (1 << n) - 1;
 
    for (int mask = 1; mask < (1 << n); ++mask){
        for (int i = 0; i < n; ++i){
            if (!(mask & (1 << i))) continue;
            int prevMask = mask ^ (1 << i);
            if (prevMask == 0) f[i][mask] = 1;
            for (int j = 0; j < n; ++j){
                if (!(prevMask & (1 << j))) continue;
                if (gcd[i][j] < k) continue;
                f[i][mask] += f[j][prevMask];
            }
        }
    }
 
    getPermutation(m);
    if (ans.size() == 0){
        cout << -1 << endl;
        return 0;
    }
    for (int i = 0; i < (int)ans.size(); ++i) cout << ans[i] << " ";
    cout << endl;
 
    return 0;
}
