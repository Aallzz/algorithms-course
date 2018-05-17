#include <bits/stdc++.h>
 
using namespace std;
 
//#define std_input_output
#ifndef std_input_output
    #define taskname "search3"
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
 
string rev(string s) {
    std::reverse(s.begin(), s.end());
    return s;
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
    string text;
    cin >> text;
    auto z = z_function(s + "#" + text);
    auto rz = z_function(rev(s) + "#" + rev(text));
 
    vector<int> zf, rzf;
 
    int len = (int)s.length();
 
    for (int i = len + 1; i < (int)z.size(); ++i) {
        zf.push_back(z[i]);
        rzf.push_back(rz[i]);
    }
 
    reverse(rzf.begin(), rzf.end());
 
//    for (auto x : zf) cout << x << " ";
 
//    cout << endl;
 
//    for (auto x : rzf) cout << x << " ";
 
//    cout << endl;
 
    vector<int> ans;
    for (size_t i = 0; i + len - 1 < zf.size(); ++i) {
        int z1 = zf[i];
        int z2 = rzf[i + len - 1];
        if (z1 + z2 >= len - 1) {
            ans.push_back((int)i + 1);
        }
    }
    cout << ans.size() << endl;
    for (int x : ans) cout << x << " ";
    cout << endl;
    return 0;
}
