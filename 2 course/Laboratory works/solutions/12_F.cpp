#include <bits/stdc++.h>
 
using namespace std;
 
//#define std_input_output
#ifndef std_input_output
    #define taskname "period"
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
auto z_function(const string& s) {
    int n = static_cast<int>(s.length());
    vector<int> z(n);
    int l = 0,
        r = -1;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) ++z[i];
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    return z;
}
 
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
    size_t n = s.length();
    auto z = z_function(s);
    for (size_t i = 0; i + i < n + 1; ++i) {
        if (static_cast<size_t>(z[i]) == n - i) {
            cout << i << endl;
            return 0;
        }
    }
    cout << n << endl;
    return 0;
}
