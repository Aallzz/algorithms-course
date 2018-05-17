#include <bits/stdc++.h>
 
using namespace std;
 
#define STD_INPUT_OUTPUT
 
#define taskname ""
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = (int)1e3 + 100;
constexpr int P = 31;
 
int get_hash(string s) {
    int res = 0;
    for (int i = 0; i < (int)s.length(); ++i) {
        res = res * P + s[i];
    }
    return res;
}
 
vector<string> gen(vector<string> g) {
    vector<string> res;
    for (int i = 0; i < (int)g.size(); ++i) {
        res.push_back(g[i] + "Aa");
        res.push_back(g[i] + "BB");
    }
    return res;
}
 
vector<string> get(int n) {
    vector<string> res{"Aa", "BB"};
 
    while ((int)res.size() < n) {
        res = gen(res);
    }
 
    return res;
}
 
int main() {
    ios_base::sync_with_stdio(false);
 
//    #ifdef Alex_PKZDL
//        ifstream cin("input.txt");
//        ofstream cout("output.txt");
//    #else
//        #ifndef STD_INPUT_OUTPUT
//            ifstream cin(taski);
//            ofstream cout(tasko);
//        #endif // STD_INPUT_OUTPUT
//    #endif // Alex_PKZDL
 
    int n; cin >> n;
 
    vector<string> res = get(n);
 
    for (int i = 0; i < n; ++i) {
        cout << res[i] << endl;
    }
    return 0;
}
