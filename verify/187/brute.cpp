#include<bits/stdc++.h>
using namespace std;

// Brute force: count numbers < N with exactly 2 prime factors (counting multiplicity)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    cin >> N;

    // Sieve to get smallest prime factor for each number
    vector<int> spf(N, 0);
    for (long long i = 2; i < N; i++) {
        if (spf[i] == 0) { // prime
            spf[i] = i;
            for (long long j = i * i; j < N; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }

    long long ans = 0;
    for (long long n = 4; n < N; n++) {
        int cnt = 0;
        long long x = n;
        while (x > 1 && cnt <= 2) {
            int p = spf[x];
            while (x % p == 0) {
                cnt++;
                x /= p;
            }
        }
        if (cnt == 2 && x == 1) ans++;
    }

    cout << ans << "\n";
    return 0;
}
