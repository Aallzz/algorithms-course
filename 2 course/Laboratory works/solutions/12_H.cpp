#include <bits/stdc++.h>
 
using namespace std;
 
//#define std_input_output
#ifndef std_input_output
    #define taskname "substrcmp"
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
 
struct string_hash {
 
    string_hash(string const& ss)
        : s(ss),  n(static_cast<int>(ss.length())), hsh(n + 1), pw(n + 1) {
        build_hash();
    }
 
 
    long long hash(int l, int r) {
        return sub_hash(l, r);
    }
 
private:
 
    void build_hash() {
        hsh.assign(n, 0);
        pw[0] = 1ll;
        for (int i = 0; i < n; ++i) {
            (hsh[i + 1] = hsh[i] * P + s[i]) %= mod;
            (pw[i + 1] = pw[i] * P) %= mod;
        }
    }
 
    long long sub_hash(int l, int r) {
        return (hsh[r] - (hsh[l] * pw[r - l]) % mod + mod) % mod ;
 
    }
 
    constexpr static long long P {52117ll};
    constexpr static long long mod {1000000007ll};
 
    string s;
    mutable int n {};
    vector<long long> hsh;
    vector<long long> pw;
};
 
int main() {
    #ifdef Alex_PKZDL
        freopen(input_file, "r", stdin);
        freopen(output_file, "w", stdout);
    #else
        #ifndef std_input_output
            freopen(taski, "r", stdin);
            freopen(tasko, "w", stdout);
        #endif
    #endif
    ios_base::sync_with_stdio(false);
 
    string s;
    cin >> s;
    string_hash str_hash(s);
 
    int q; cin >> q;
    while (q--) {
        int l, r, ll, rr;
        cin >> l >> r >> ll >> rr; --l; --ll;
        cout << (str_hash.hash(l, r) == str_hash.hash(ll, rr) ? "Yes" : "No") << endl;
    }
    return 0;
}
