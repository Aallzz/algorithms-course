#include <bits/stdc++.h>
 
using namespace std;
 
//#define std_input_output
#ifndef std_input_output
    #define taskname "z"
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
    auto z = z_function(s);
    z.erase(z.begin());
    for (auto x : z) cout << x << " ";
    cout << endl;
    return 0;
}
