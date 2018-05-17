#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "garland"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)1e3 + 10;
const double eps = 1e-9;
 
int n;
double A;
double h[N];
 
bool f(double curH){
    double mn = min(curH, A);
    h[0] = A, h[1] = curH;
    for (int i = 2; i < n; ++i){
        h[i] = 2 * h[i - 1] - h[i - 2] + 2;
        mn = min(mn, h[i]);
    }
    return mn > eps;
}
 
int main()
{
    #ifndef Alex_PKZDL
        freopen(taski, "r", stdin);
        freopen(tasko, "w", stdout);
    #endif // AlexPKZDL
    ios_base::sync_with_stdio(false);
 
    cin >> n >> A;
 
    double l = 0, r = A;
    for (int i = 0; i < 300; ++i){
        double mid = (l + r) / 2.0;
        if (f(mid)) r = mid;
        else l = mid;
    }
 
    cout << setprecision(2) << fixed;
    cout << h[n - 1] << endl;
    return 0;
}
