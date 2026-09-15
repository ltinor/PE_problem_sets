#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int K;
        cin >> K;

        // Precompute digit powers: 0^K .. 9^K
        ll pow10[10];
        for (int d = 0; d <= 9; d++) {
            ll p = 1;
            for (int k = 0; k < K; k++) p *= d;
            pow10[d] = p;
        }

        // Upper bound: for n-digit number, max sum = n * 9^K
        // When n * 9^K < 10^(n-1), no more numbers possible
        // For K=6: 9^6=531441, 7*531441=3720087 which is 7-digit, 10^6=1000000
        // So upper bound ~7*9^K, and we can safely check up to, say, 10^7 for K≤6
        ll upper = 1;
        for (int d = 1; ; d++) {
            if (d * pow10[9] < upper) break;
            upper *= 10;
        }
        // upper is 10^(max_digits), e.g., for K=6: upper = 10^7 = 10000000
        // But that's 8-digit loop. Let's bound it tighter:
        // We only need up to d * 9^K for d digits. Since K≤6, max d ≈ 7.
        // So upper = 7*9^K + 1, which for K=5 is 7*59049+1=413344, for K=6 is 7*531441+1=3720088

        upper = 7 * pow10[9] + 1;

        ll total = 0;
        for (ll n = 2; n <= upper; n++) {
            ll sum = 0;
            ll tmp = n;
            while (tmp > 0) {
                sum += pow10[tmp % 10];
                tmp /= 10;
            }
            if (sum == n) {
                total += n;
            }
        }
        cout << total << "\n";
    }
    return 0;
}
