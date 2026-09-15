#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const double PI = acos(-1.0);

int main() {
    int n = 10000;
    int K = (int)(n * log(PI + 1.0));
    vector<double> f(K + 1);
    for (int k = 0; k <= K; k++) f[k] = exp((double)k / n) - 1.0;
    int M = K + 1;
    
    ll cnt = 0;
    for (int i = 0; i < M; i++) {
        double target = PI - f[i];
        int lo = i, hi = M - 1;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (f[mid] <= target + 1e-15) lo = mid;
            else hi = mid - 1;
        }
        cnt += lo - i + 1;
    }
    
    cout << "M = " << M << endl;
    cout << "Pairs = " << cnt << endl;
    cout << "Memory (16B) = " << (cnt * 16) / 1e9 << " GB" << endl;
}
