#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "sequences"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = 7;
const long long mod = (long long)999999937;
 
struct matrix{
    long long a[N][N];
    int n, m;
 
    matrix(int n, int m) : n(n), m(m) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) a[i][j] = 0;
    };
 
    matrix operator *(matrix b){
        matrix res(n, b.m);
        for (int k = 0; k < m; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < b.m; ++j)
                        (res.a[i][j] += (a[i][k] * b.a[k][j]) % mod)%=mod;
        return res;
    }
};
 
matrix r(5, 5);
matrix e(5, 5);
 
matrix power(matrix a, long long n){
    if (n == 0LL) return e;
    if (n % 2LL == 0LL){
        matrix x = power(a, n / 2LL);
        return x * x;
    } else {
        return a * power(a, n - 1LL);
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
 
    long long n;
    while (cin >> n){
        if (n == 0LL) return 0;
        n--;
 
        for (int i = 0; i < 5; ++i){
            if (i != 2 && i != 4){
                for (int j = 0; j < 5; ++j) r.a[i][j] = 1;
            } else {
                for (int j = 0; j < 3; ++j) r.a[i][j] = 1;
                for (int j = 3; j < 5; ++j) r.a[i][j] = 0;
            }
            e.a[i][i] = 1;
        }
 
        r = power(r, n);
 
        long long ans = 0LL;
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                (ans += r.a[i][j])%=mod;
        cout << ans << endl;
    }
    return 0;
}
