#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    const int MAX = 10000000;
    vector<bool> is_prime(MAX + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= MAX; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }
    cerr << "Sieve done" << endl;

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
            cout << "K=" << cnt << ": " << odd << "\n";
            if (cnt >= 10) break;
        }
    }
    if (cnt < 10) cout << "Only found " << cnt << " up to " << MAX << "\n";
}
