#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)1e5 + 10;
const long long linf = (long long)1e12 + 10;
 
long long a[N], b[N], t[N], cnt[N], c[N];
long long n, m, p;
 
void MergeSort(int l, int r){
    if (l + 1 >= r) return ;
    int mid = (l + r) / 2;
 
    MergeSort(l, mid);
    MergeSort(mid, r);
 
    int k = l;
    int q = mid;
 
    for (int i = l; i < r; ++i){
        if ((k < mid && cnt[k] < cnt[q]) || q >= r)
            c[i] = cnt[k++];
        else
            c[i] = cnt[q++];
    }
 
    for (int i = l; i < r; ++i){
        cnt[i] = c[i];
    }
}
 
bool f(long long time){
    for (int i = 0; i < n; ++i){
        long long freeTime = time - (t[i] + b[i]);
        if (freeTime < 0LL) cnt[i] = 0LL;
        else cnt[i] = (a[i] == 0LL ? linf : freeTime / a[i]);
    }
    MergeSort(0, (int)n);
//    sort(cnt, cnt + n);
    reverse(cnt, cnt + n);
    long long sum = p;
    for (int i = 0; i < (int)min(m, n); ++i) sum -= cnt[i];
 
    return (sum <= 0LL);
}
 
int main()
{
    ios_base::sync_with_stdio(false);
 
    #ifndef Alex_PKZDL
    ifstream cin("supermarket.in");
    ofstream cout("supermarket.out");
    #endif // Alex_PKZDL
 
    cin >> n;
 
    for (int i = 0; i < n; ++i){
        cin >> a[i] >> b[i] >> t[i];
    }
 
    cin >> m >> p;
 
    long long l = 0LL, r = linf;
 
    while (r - l > 1LL){
        long long mid = (l + r) >> 1LL;
        if (f(mid)) r = mid;
        else l = mid;
    }
 
    if (f(l)) cout << l << endl;
    else cout << r << endl;
    return 0;
}
