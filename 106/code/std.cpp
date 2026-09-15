#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Catalan numbers: C(2k,k)/(k+1)
ll catalan[15];
ll C[30][30];

void init() {
    // Binomial coefficients
    for (int i = 0; i <= 25; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
    // Catalan numbers for k=0..12
    for (int k = 0; k <= 12; k++) {
        catalan[k] = C[2*k][k] / (k + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();

    int n;
    cin >> n;

    ll ans = 0;
    // For each equal subset size k >= 1
    for (int k = 1; k <= n/2; k++) {
        // Choose 2k elements from n: C(n, 2k)
        ll choose_2k = C[n][2*k];
        // Total unordered splits of 2k into two k-sets: C(2k, k) / 2
        ll total_splits = C[2*k][k] / 2;
        // Splits that DON'T need testing = Catalan(k)
        ll need_test = total_splits - catalan[k];
        ans += choose_2k * need_test;
    }

    cout << ans << "\n";
    return 0;
}
