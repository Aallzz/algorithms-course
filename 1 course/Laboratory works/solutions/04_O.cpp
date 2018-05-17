#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "bridge"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)2e2 + 10;
const int inf = (int)1e9 + 10;
 
int f[N][N];
int x, a, y, b, l;
 
bool check(int len){
    for (int i = 0; i <= l; ++i)
        for (int j = 0; j <= x; ++j) f[i][j] = inf;
 
    f[0][0] = 0;
 
    for (int i = 0; i < l; ++i){
        for (int j = 0; j <= x; ++j){
            for (int k = 0; k + j <= x; ++k){
                f[i + 1][k + j] = min(f[i + 1][k + j], f[i][j] + max(0, (len - a * k + b - 1) / b));
            }
        }
    }
 
    bool was = false;
    for (int i = 0; i <= x; ++i) if (f[l][i] <= y) was = true;
    return was;
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
 
    cin >> x >> a >> y >> b >> l;
 
    int l = 0, r = a * x + b * y;
    while (r - l > 1){
        int mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    if (check(r)) cout << r << endl;
    else cout << l << endl;
    return 0;
}
