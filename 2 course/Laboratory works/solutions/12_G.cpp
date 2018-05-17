#include <bits/stdc++.h>
 
using namespace std;
 
//#define std_input_output
#ifndef std_input_output
    #define taskname "search4"
    #define taski taskname".in"
    #define tasko taskname".out"
#endif
 
constexpr int N {1666666};
constexpr int LG {35};
constexpr int A {30};
constexpr int K {21};
constexpr int inf {1999999999};
constexpr char mn_char {char('a' - 1)};
 
int c[LG][N], p[LG][N], cnt[N], lg, pn[N], cn[N];
int sa[N];
 
void build_suffix_array(string const& t){
    int n = static_cast<int>(t.length());
    for (int i = 0; i < N; ++i) cnt[i] = 0;
    for (int i = 0; i < n; ++i) cnt[t[i] - mn_char]++;
    for (int i = 1; i < A; ++i) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i)
        p[lg][--cnt[t[i] - mn_char]] = i;
    c[lg][p[lg][0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; ++i){
        if (t[p[lg][i]] != t[p[lg][i - 1]]) ++classes;
        c[lg][p[lg][i]] = classes - 1;
    }
 
    for (int h = 0; (1 << h) <= n; ++h){
        for (int i = 0; i < n; ++i){
            pn[i] = p[lg][i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        for (int i = 0; i < classes + 100; ++i) cnt[i] = 0;
        for (int i = 0; i < n; ++i)
            ++cnt[c[lg][pn[i]]];
        for(int i = 1; i < classes; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n-1; i >= 0; --i)
            p[lg + 1][--cnt[c[lg][pn[i]]]] = pn[i];
        cn[p[lg + 1][0]] = 0;
        classes = 1;
        for (int i = 1; i < n; ++i){
            int mid1 = (p[lg + 1][i] + (1 << h)) % n,
                mid2 = (p[lg + 1][i - 1] + (1 << h)) % n;
            if (mid1 >= 1000006 || mid2 >= 1000006){
                cout << -1 << endl;
                exit(0);
            }
            if (c[lg][p[lg + 1][i]] != c[lg][p[lg + 1][i - 1]] || c[lg][mid1] != c[lg][mid2])
                classes++;
            cn[p[lg + 1][i]] = classes - 1;
        }
        for (int i = 0; i < n; ++i)
            c[lg + 1][i] = cn[i];
        ++lg;
        if (classes == n) break;
    }
}
 
string s;
 
int compare(string const& s1, int pos) {
    int n1 = static_cast<int>(s1.length());
    int n = static_cast<int>(s.length());
    for (int i = 0; i < n1 && sa[pos] + i < n; ++i) {
        if (s1[i] < s[sa[pos] + i]) return -1;
        if (s1[i] > s[sa[pos] + i]) return +1;
    }
    return 0;
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
 
 
    vector<string> sss;
    int ccnt; cin >> ccnt;
    for (int i = 0; i < ccnt; ++i) {
        string ssss; cin >> ssss;
        sss.emplace_back(ssss);
    }
 
    cin >> s;
    s += mn_char;
    build_suffix_array(s);
    int n = static_cast<int>(s.length());
 
    for (int i = 0; i < n; ++i) sa[cn[i]] = i;
 
    for (const auto& ss : sss) {
        int l {0}, r {n};
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (compare(ss, mid) <= 0) {
                r = mid;
            } else {
                l = mid;
            }
        }
        if (compare(ss, l) == 0 || compare(ss, r) == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
