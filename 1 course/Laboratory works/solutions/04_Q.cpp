#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "nice3"
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = 65;
const int base = 1000*1000*1000;
 
int mod, m;
 
struct bigInt{
    vector<int> a;
 
    bigInt(){
        a.push_back(0);
    }
 
    bigInt operator = (string s){
        a.clear();
        for (int i=(int)s.length(); i>0; i-=9)
            if (i < 9)
                a.push_back (atoi (s.substr (0, i).c_str()));
            else
                a.push_back (atoi (s.substr (i-9, 9).c_str()));
        return *this;
    }
 
    bool isZero(){
        return (a.size() == 0 || (a.size() == 1 && a[0] == 0));
    }
 
    void print(){
        printf ("%d", a.empty() ? 0 : a.back());
        for (int i=(int)a.size()-2; i>=0; --i)
            printf ("%09d", a[i]);
    }
 
    bigInt operator / (int b){
        int carry = 0;
        for (int i=(int)a.size()-1; i>=0; --i) {
            long long cur = a[i] + carry * 1ll * base;
            a[i] = int (cur / b);
            carry = int (cur % b);
        }
        while (a.size() > 1 && a.back() == 0)
            a.pop_back();
        return *this;
    }
 
    int operator % (int b){
        if (a.size() == 0) return 0;
        return a[0] % b;
    }
 
    bigInt operator -(int b){
        a[0] -= b;
        int carry = (a[0] < 0);
        if (carry) a[0] += base;
        for (int i = 1; carry; ++i) {
            a[i] -= carry;
            carry = a[i] < 0;
            if (carry)  a[i] += base;
        }
        while (a.size() > 1 && a.back() == 0)
            a.pop_back();
        return *this;
    }
 
 
};
struct matrix
{
    int n, m, a[N][N];
 
    matrix(){
        n = 1, m = 1;
        a[0][0] = 0;
    }
 
    matrix(int n, int m) : n(n), m(m){
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = 0;
    }
 
    void init(int _n, int _m){
        n = _n, m = _m;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = 0;
    }
 
    matrix operator * (matrix b){
        matrix res(n, b.m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < b.m; ++j)
                for (int k = 0; k < m; ++k)
                    (res.a[i][j] += a[i][k] * b.a[k][j]) %= mod;
        return res;
    }
};
 
matrix e, a;
bigInt n;
 
matrix power(matrix a, bigInt n){
//    n.print(); cout << endl;
//    if (n.isZero())
//        return e;
//    if (n % 2 == 0){
//        cout << "2" << endl;
//        matrix x = power(a, n / 2);
//        return x * x;
//    } else {
//        cout << "1" << endl;
//        return (a * power(a, n - 1));
//    }
    matrix p(a.n, a.m);
    p = e;
 
    while (!n.isZero()){
        if (n % 2 != 0){
            p = p * a;
            n = n - 1;
        }
        n = n / 2;
        if (!n.isZero()) a = a * a;
    }
    return p;
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
 
    string s; cin >> s; n = s;
    cin >> m >> mod;
 
    e.init((1 << m), (1 << m));
    a.init((1 << m), (1 << m));
 
    for (int i = 0; i < (1 << m); ++i) e.a[i][i] = 1;
 
    for (int mask1 = 0; mask1 < (1 << m); ++mask1){
        for (int mask2 = 0; mask2 < (1 << m); ++mask2){
            bool p = true;
            for (int i = 0; i < m - 1; ++i){
                int bit1 = (mask1 & (1 << i)) != 0;
                int bit2 = (mask1 & (1 << (i + 1))) != 0;
                int bit3 = (mask2 & (1 << i)) != 0;
                int bit4 = (mask2 & (1 << (i + 1))) != 0;
                if (bit1 == bit2 && bit2 == bit3 && bit3 == bit4){
                    p = false;
                }
            }
            if (p){
                a.a[mask1][mask2] = 1;
            }
        }
    }
 
    n = n - 1;
    a = power(a, n);
 
    int ans = 0;
    for (int mask1 = 0; mask1 < (1 << m); ++mask1){
        for (int mask2 = 0; mask2 < (1 << m); ++mask2){
            (ans += a.a[mask1][mask2]) %= mod;
        }
    }
 
    cout << ans << endl;
    return 0;
}
