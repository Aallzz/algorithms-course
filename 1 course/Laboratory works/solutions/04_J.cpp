#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname ""
#define taski taskname".in"
#define tasko taskname".out"
 
const int N = (int)1e4 + 10;
 
string s, t;
int f[2][N];
vector<int> v1, v2;
 
int lcsLen(int ii, int jj, int iii, int jjj){
 
    v1.clear();
    v1.push_back(0);
    int cur = 0;
    for (int i = 0, k = iii; k <= jjj + 1; ++i, ++k) f[1][i] = f[0][i] = 0;
 
    for (int i = ii; i <= jj; ++i){
        for (int j = iii, k = 0; j <= jjj; ++j,++k){
            if (s[i] == t[j])
                f[cur ^ 1][k] = f[cur][k - 1] + 1;
            else
                f[cur ^ 1][k] = max(f[cur ^ 1][k - 1], f[cur][k]);
        }
        cur ^= 1;
    }
 
    int mx = 0;
    for (int i = iii, k = 0; i <= jjj; ++i, ++k) mx = max(f[cur][k], mx), v1.push_back(f[cur][k]);
    v1.push_back(0);
    return mx;
}
 
int lcsLenReverse(int ii, int jj, int iii, int jjj){
 
    v2.clear();
    int cur = 0;
    v2.push_back(0);
    for (int i = 0, k = iii; k <= jjj + 1; ++i, ++k) f[0][i] = f[1][i] = 0;
 
    for (int i = jj; i >= ii; --i){
        for (int j = jjj, k = jjj - iii; j >= iii; --j, --k){
            if (s[i] == t[j])
                f[cur ^ 1][k] = f[cur][k + 1] + 1;
            else
                f[cur ^ 1][k] = max(f[cur ^ 1][k + 1], f[cur][k]);
        }
        cur ^= 1;
    }
 
    int mx = 0;
    for (int i = iii, k = 0; i <= jjj; ++i, ++k) mx = max(f[cur][k], mx), v2.push_back(f[cur][k]);
    v2.push_back(0);
    return mx;
}
 
string lcs(int i, int j, int ii, int jj){
    if (i > j || ii > jj) return "";
 
    if (i == j){
        for (int k = ii; k <= jj; ++k) if (s[i] == t[k])
            return string(1, s[i]);
        return "";
    }
 
    if (ii == jj){
         for (int k = i; k <= j; ++k) if (s[k] == t[jj])
            return string(1, t[jj]);
        return "";
    }
 
    int mdS = (j + i) / 2;
 
    int lcslen = lcsLen(i, j, ii, jj);
 
    lcsLen(i, mdS, ii, jj);
    lcsLenReverse(mdS + 1, j, ii, jj);
//    reverse(v2.begin(), v2.end());
 
//    for (int k = i; k <= j; ++k) cout << s[k] << (k == mdS ? " " : ""); cout << endl;
//    for (int k = ii; k <= jj; ++k) cout << t[k]; cout << endl;
//    cout << v1.size() << ": "; for (int k1 = ii; k1 <= jj; ++k1) cout << v1[k1 - ii] << " "; cout << endl;
//    cout << v2.size() << ": "; for (int k1 = ii; k1 <= jj; ++k1) cout << v2[k1 - ii] << " "; cout << endl;
 
    if (lcslen == 0) return "";
 
    int mdT = ii - 1;
    for (; mdT <= jj; ++mdT)
        if ((mdT == -1 ? 0 : v1[mdT - (ii - 1)]) + v2[mdT - (ii - 1) + 1]== lcslen) break;
//    for (; mdT <= jj; mdT++){
//        if (lcsLen(i, mdS, ii, mdT) + lcsLen(mdS + 1, j, mdT + 1, jj) == lcslen) break;
//    }
 
    string res1 = lcs(i, mdS, ii, mdT);
    string res2 = lcs(mdS + 1, j, mdT + 1, jj);
 
    return res1 + res2;
 
//    if (s.length() == 0 || t.length() == 0) return "";
 
//    if (s.length() == 1){
//        for (int j = 0; j < (int)t.length(); ++j)
//            if (s[0] == t[j]) return s;
//        return "";
//    }
//
//    int mdS = s.length() / 2;
//
//    string sLeft = s.substr(0, mdS);
//    string sRight = s.substr(mdS, s.length() - mdS);
//
//    int lcslen = lcsLen(s, t);
//
//    int mdT = 0;
//    for (; mdT < (int)t.length(); ++mdT){
//        if (lcsLen(sLeft, t.substr(0, mdT)) +  lcsLen(sRight, t.substr(mdT, t.length() - mdT)) == lcslen) break;
//    }
//
//    string tLeft = t.substr(0, mdT);
//    string tRight = t.substr(mdT, t.length() - mdT);
//
//    string res1 = lcs(sLeft, tLeft);
//    string res2 = lcs(sRight, tRight);
//
//    return res1 + res2;
 
}
int main()
{
    ios_base::sync_with_stdio(false);
 
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
//        ifstream cin(taski);
//        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    cin >> s >> t;
    cout << lcs(0, s.length() - 1, 0, t.length() - 1) << endl;
    return 0;
}
