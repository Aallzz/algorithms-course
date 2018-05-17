#include <bits/stdc++.h>
  
using namespace std;
  
//#define std_input_output
#ifndef std_input_output
    #define taskname "prefix"
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
  
constexpr size_t N {122};
  
vector<int> prefix_function(string const& s) {
    size_t n = s.length();
    vector<int> pi(n);
    for (size_t i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (s[i] != s[j] && j > 0)
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
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
    string t;
  
    cin >> s >> t;
  
    string text = s;
    auto pi = prefix_function(s);
  
    for (int x : pi) {
        cout << x << " ";
    }
    cout << endl;
  
    return 0;
}
