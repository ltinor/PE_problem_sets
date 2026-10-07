#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    // Verify: check a specific number is a counterexample
    const int MAX = 20000;
    vector<bool> is_prime(MAX + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= MAX; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }

    int cnt = 0;
    for (int odd = 9; odd <= MAX; odd += 2) {
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
            cout << "K=" << cnt << ": " << odd;
            cout << " (composite: ";
            // find a factor
            for (int d = 3; d * d <= odd; d += 2) {
                if (odd % d == 0) {
                    cout << d << "*" << odd/d;
                    break;
                }
            }
            cout << ")\n";
        }
    }
}
