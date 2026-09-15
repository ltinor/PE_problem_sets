#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 179: count n < N where d(n) == d(n+1)
// N <= 10^7
// Use sieve to compute divisor counts

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    if (N < 2 || N > 10000000) return 1;

    // d[i] = number of divisors of i
    vector<int> d(N + 2, 0);

    // Sieve: for each i, add 1 to multiples
    for (int i = 1; i <= N + 1; i++) {
        for (int j = i; j <= N + 1; j += i) {
            d[j]++;
        }
    }

    int ans = 0;
    for (int n = 2; n < N; n++) {
        if (d[n] == d[n + 1]) {
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
