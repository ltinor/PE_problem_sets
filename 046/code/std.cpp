#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    int bound = 2000000;
    vector<bool> is_prime;
    int last_processed = 7; // last odd processed; start from 9
    int cnt = 0;

    while (true) {
        // Build sieve for current bound
        is_prime.assign(bound + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (ll i = 2; i * i <= bound; i++) {
            if (is_prime[i]) {
                for (ll j = i * i; j <= bound; j += i) {
                    is_prime[j] = false;
                }
            }
        }

        // Process odds from last_processed+2 to bound
        for (int odd = last_processed + 2; odd <= bound; odd += 2) {
            if (is_prime[odd]) continue;

            bool ok = false;
            for (int s = 1; ; s++) {
                int ts = 2 * s * s;
                if (ts >= odd) break;
                if (is_prime[odd - ts]) {
                    ok = true;
                    break;
                }
            }
            if (!ok) {
                cnt++;
                if (cnt == K) {
                    cout << odd << "\n";
                    return 0;
                }
            }
        }

        last_processed = bound;
        if (last_processed % 2 == 0) last_processed--; // keep odd
        bound *= 2;
    }
}
