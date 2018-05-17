#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "chip"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr size_t N {54444 + 54444};
 
int n;
int color[N], nm[N];
pair<int, int> ps[N];
int used[N], put[N];
int step = 1;
 
vector<int> mem;
 
bool solve(int v) {
 
    mem.push_back(v);
    put[v] = color[nm[v]];
    put[v ^ ps[nm[v]].first ^ ps[nm[v]].second] = -color[nm[v]];
 
    int nxt = v % (n + n) + 1;
    int prv = (v - 2 + n + n) % (n + n) + 1;
    bool ok = true;
 
    if (color[nm[nxt]] == color[nm[v]]) {
        if (put[nxt] == color[nm[v]])
            return false;
        if (put[nxt] != -color[nm[v]]) {
            put[nxt] = -color[nm[v]];
            put[nxt ^ ps[nm[nxt]].first ^ ps[nm[nxt]].second] = color[nm[v]];
            ok &= solve(nxt ^ ps[nm[nxt]].first ^ ps[nm[nxt]].second);
        }
    }
    if (color[nm[prv]] == color[nm[v]]) {
        if (put[prv] == color[nm[v]])
            return false;
        if (put[prv] != -color[nm[v]]) {
            put[prv] = -color[nm[v]];
            put[prv ^ ps[nm[prv]].first ^ ps[nm[prv]].second] = color[nm[v]];
            ok &= solve(prv ^ ps[nm[prv]].first ^ ps[nm[prv]].second);
        }
    }
    return ok;
}
 
void clear() {
    for (int v : mem) {
        put[v] = put[v ^ ps[nm[v]].first ^ ps[nm[v]].second] = 0;
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
 
#ifdef Alex_PKZDL
    ifstream cin(input_file);
    ofstream cout(output_file);
#else
    ifstream cin(taski);
    ofstream cout(tasko);
#endif
 
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> color[i];
    }
 
    for (int i = 1; i <= n + n; ++i) {
        cin >> nm[i];
        if (ps[nm[i]].first)
            ps[nm[i]].second = i;
        else
            ps[nm[i]].first = i;
    }
 
    for (int i = 1; i <= n; ++i) {
        if (!solve(ps[i].first)) {
            clear();
            mem.clear();
            if (!solve(ps[i].second)) {
                cout << "NO" << endl;
                return 0;
            }
        }
        mem.clear();
    }
 
    cout << "YES" << endl;
    for (int i = 1; i <= n; ++i) {
        if (put[ps[i].first] > 0) cout << ps[i].first << " ";
        else cout << ps[i].second << " ";
    }
 
    return 0;
}
