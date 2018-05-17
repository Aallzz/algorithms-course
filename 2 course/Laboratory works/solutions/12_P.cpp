#include <bits/stdc++.h>
 
using namespace std;
 
#define std_input_output
#ifndef std_input_output
    #define taskname "dictionary"
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr size_t N {255555};
constexpr long long mod {1000000007};
 
 
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
 
vector<int> get_pi(int len, int alpha) {
    string x;
    for (int i = 0; i < len; ++i) {
        char c = char(rand() % alpha + 'a');
        x += c;
    }
    return prefix_function(x);
}
 
long long dfs(string const& s, vector<int> const& pi, int alpha) {
    if (s.length() == pi.size()) {
        return pi == prefix_function(s);
    }
    long long res {};
    for (int i = 0; i < alpha; ++i) {
        res += dfs(s + char(i + 'a'), pi, alpha);
    }
    return res;
}
 
long long brute(vector<int> const& pi, int alpha) {
    return dfs("", pi, alpha);
}
 
long long solve(vector<int> const& pi, int alpha) {
    long long ans = 1ll;
    vector<int> c(pi.size());
    c[0] = alpha;
    for (size_t i = 1; i < pi.size(); ++i) {
        if (pi[i] == pi[i - 1] + 1)
            c[i] = 1;
        else
            if (pi[i] == 0)
                if (pi[i - 1] + 1 >= (int)i)
                    c[i] = alpha - 1;
                else
                    if (pi[i - 1] == 0) {
                        c[i] = alpha - 1;
                    } else {
                        c[i] = alpha - 1;
                        int j = (int)i;
                        while (j - 1 >= 0 && pi[pi[j - 1]])
                            j = pi[j - 1];
                        c[i] = c[pi[j - 1]] - 1;
//                        if (pi[pi[i - 1]] == 0)
//                            c[i] = c[pi[i - 1]] - 1;
//                        else if (pi[pi[pi[i - 1] - 1] - 1] == 0)
//                            c[i] = c[pi[pi[i - 1] - 1] - 1] - 2;
//                        else if (pi[pi[pi[pi[i - 1] - 1] - 1] - 1] == 0)
//                            c[i] = c[pi[pi[pi[i - 1] - 1] - 1] - 1] - 3;
//                        else if (pi[pi[pi[pi[pi[i - 1]- 1] - 1] - 1] - 1] == 0)
//                                c[i] = c[pi[pi[pi[pi[i - 1] - 1] - 1] - 1] - 1] - 4;
//                            else
 
//                            c[i] = alpha - 1;
                    }
            else
                c[i] = 1;
    }
//    for (int i = 0; i < c.size(); ++i) cout << c[i] << " "; cout << endl;
    for (size_t i = 0; i < c.size(); ++i) (ans *= 1ll * c[i]) %= mod;
    return ans;
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
 
    int n, m;
    cin >> n >> m;
    vector<int> pi(n);
    for (size_t i = 0; i < pi.size(); ++i) cin >> pi[i + 1];
    cout << solve(pi, m);
 
    return 0;
}
