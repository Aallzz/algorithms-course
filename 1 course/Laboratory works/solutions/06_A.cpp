#include <bits/stdc++.h>
 
using namespace std;
 
#define taskname "set"
#define taski taskname".in"
#define tasko taskname".out"
 
constexpr int N = 1003273;
constexpr int mod = N;
 
vector<int> hs[N + 1000];
 
int get_hash(int x) {
    return abs(x) % mod;
}
 
bool exists(int x) {
    return find(hs[get_hash(x)].begin(), hs[get_hash(x)].end(), x) != hs[get_hash(x)].end();
}
 
void insert_element(int x) {
    if (exists(x)) return ;
    hs[get_hash(x)].push_back(x);
}
 
void delete_element(int x) {
    if (!exists(x)) return ;
    hs[get_hash(x)].erase(find(hs[get_hash(x)].begin(), hs[get_hash(x)].end(), x));
}
 
int main() {
    ios_base::sync_with_stdio(false);
 
    #ifdef Alex_PKZDL
        ifstream cin("input.txt");
        ofstream cout("output.txt");
    #else
        ifstream cin(taski);
        ofstream cout(tasko);
    #endif // Alex_PKZDL
 
    string type;
    int x;
 
    while (cin >> type >> x) {
        switch (type[0]) {
            case 'i' : insert_element(x); break;
            case 'e' : cout << (exists(x) ? "true" : "false") << endl; break;
            case 'd' : delete_element(x); break;
        }
    }
    return 0;
}
