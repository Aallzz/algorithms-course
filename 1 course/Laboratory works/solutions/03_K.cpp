#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (int)1e5 + 10;
 
pair<double, double> q[N];
pair<double, int> h[N];
int n, k;
 
int kPartition(int l, int r){
    if (l == r) return l;
    int i = l - 1;
    int j = r;
    while (true){
        while (h[++i].first < h[r].first);
        while (h[r].first < h[--j].first && j > l);
        if (i >= j) break;
        swap(h[i], h[j]);
    }
    swap(h[i], h[r]);
    return i;
}
 
pair<double, int> getKthElement(int l, int r, int k){
    while (true){
        int m = kPartition(l, r);
        if (k < m){
            r = m - 1;
        } else if (m < k){
            l = m + 1;
        } else
            return h[k];
    }
}
 
int ans[N];
 
bool f(pair<double, double> p){
    for (int i = 0; i < n; ++i)
        h[i] = make_pair(q[i].first * p.second - q[i].second * p.first, i);
 
    pair<double, int> cur = getKthElement(0, n - 1, k - 1);
 
    double sum = 0;
 
    for (int i = 0, kk = 0; i < n && kk < k; ++i){
        if (h[i].first <= cur.first){
            sum += h[i].first;
            ans[kk++] = h[i].second + 1;
        }
    }
 
    return (sum < 0);
}
 
int main()
{
    freopen("kbest.in", "r", stdin);
    freopen("kbest.out", "w", stdout);
 
    scanf("%d%d", &n, &k);
 
    if (n == 1) {printf("1"); return 0;}
 
    double mx = 0;
 
    for (int i = 0; i < n; ++i){
        int x, y; scanf("%d%d", &x, &y);
        q[i] = make_pair(y, x);
        mx = max((x + 0.0) / (y + 0.0), mx);
    }
 
    double l = 0, r = mx;
 
    for (int i = 0; i < 50; ++i){
        double mid = (l + r) / 2;
        if (f(make_pair(1.0 / sqrt(mid * mid + 1), mid / sqrt(mid * mid + 1)))) l = mid;
        else r = mid;
    }
 
    for (int i = 0; i < k; ++i) printf("%d ", ans[i]);
 
    return 0;
}
