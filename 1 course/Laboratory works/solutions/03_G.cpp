#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned long long ull;
 
const int N = (int)1e5 + 10;
const int M = 92788;
vector<unsigned int> x;
unsigned int cur = 0;
unsigned int a, b;
int t, n;
unsigned int nm[N], c[N];
//vector<ull> bucket[N];
unsigned int radix[66666];
unsigned int y[N];
 
unsigned int nextRand24(){
    cur = cur * a + b;
    return (cur >> 8);
}
 
unsigned int nextRand32(){
    unsigned int a = nextRand24(),
                 b = nextRand24();
    return (a << 8) ^ b;
}
 
clock_t start;
 
void RadixSort(vector<unsigned int> &p){
    int n = p.size();
    unsigned int mod = 65535;
    unsigned int shift = 0;
    while (shift < 32){
        for (int i = 0; i < 65536; ++i) radix[i] = 0;
        for (int i = 0; i < n; ++i){
            unsigned int d = (p[i] >> shift) & mod;
            radix[d]++;
        }
        int cnt = 0;
        for (int i = 0; i < 65536; ++i) {
            int tmp = radix[i];
            radix[i] = cnt;
            cnt += tmp;
        }
        for (int i = 0; i < n; ++i){
            unsigned int d = (p[i] >> shift) & mod;
            y[radix[d]] = p[i];
            radix[d]++;
        }
        for (int i = 0; i < n; ++i) p[i] = y[i];
        shift += 16;
    }
//    if (p.size() != 0) {cout << "p: "; for (int i = 0; i < n; ++i) cout << p[i] << " "; cout << endl;}
//    if (p.size() != 0) {cout << "p: "; for (int i = 0; i < n; ++i) cout << p[i] << " "; cout << endl;}
 
}
 
void MergeSort(int l, int r){
    if (l + 1 >= r) return ;
    int mid = (l + r) / 2;
    MergeSort(l, mid);
    MergeSort(mid, r);
 
    int k = l;
    int q = mid;
 
    for (int i = l; i < r; ++i){
        if ((k < mid && x[k] < x[q]) || q >= r)
            c[i] = x[k++];
        else
            c[i] = x[q++];
    }
 
    for (int i = l; i < r; ++i){
        x[i] = c[i];
    }
}
 
//void bucketSort(int l, int r){
//    if (l == r) return ;
//
//    ull mn = x[0];
//    ull mx = x[0];
//
//    for (int i = l; i < r; ++i) mn = min(mn, x[i]), mx = max(mx, x[i]);
//
//    ull cntbucket = ((mx - mn) / (ull)M) + 1;
//
//    for (int i = 0; i < (int)cntbucket; ++i)
//        bucket[i].clear();
//
////////////    cout << "Time 1: " << ((clock() - start + 0.0) / CLOCKS_PER_SEC) << endl;
//    for (int i = l; i < r; ++i){
//        bucket[(x[i] - mn) / M].push_back(x[i]);
////////////        cout << (x[i] - mn) / M << " " << cntbucket << endl;
//    }
//
//
//    int sz = 0;
//
//    for (int i = 0; i < (int)cntbucket; ++i){
//        if (bucket[i].empty()) continue;
//        RadixSort(bucket[i]);
////        if (bucket[i].size() != 0) {
////            cout << bucket[i].size() << endl;
////            cout << "Time " <<  i + 2 << ": " << ((clock() - start + 0.0) / CLOCKS_PER_SEC) << endl;
////        }
//        for (int j = 0; j < (int)bucket[i].size(); ++i) x[sz++] = bucket[i][j];
////        if (bucket[i].size() != 0) {
////            cout << bucket[i].size() << endl;
////            cout << "Time " <<  i + 2 << ": " << ((clock() - start + 0.0) / CLOCKS_PER_SEC) << endl;
////        }
//    }
//}
int main()
{
    ios_base::sync_with_stdio(false);
    ifstream cin("buckets.in");
    ofstream cout("buckets.out");
    cin >> t >> n;
    cin >> a >> b;
//    t = 1, n = 6, a = 239, b = 13;
//    start = clock();
    x.resize(n);
    while (t--){
        for (int i = 0; i < n; ++i) x[i] = nextRand32();
//        for (int i = 0; i < n; ++i) cout << x[i] << " ";
//        cout << endl;
 
//        bucketSort(0, n);
          RadixSort(x);
//        for (int i = 0; i < n; ++i) cout << x[i] << " ";
//        cout << endl;
 
        ull ans = 0LL;
        for (int i = 0; i < n; ++i) ans += ((ull)i + 1LL) * (ull)x[i];
        cout << ans << endl;
    }
    return 0;
}
