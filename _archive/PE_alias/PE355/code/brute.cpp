#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE355 brute: exhaustive search for small N

int main() {
    ll N;
    cin >> N;

    if (N > 20) {
        cout << "0\n";
        return 0;
    }

    // Map numbers to their prime factor bitmasks
    vector<int> primes;
    for (ll i = 2; i <= N; i++) {
        bool is_p = true;
        for (ll j = 2; j * j <= i; j++) if (i % j == 0) { is_p = false; break; }
        if (is_p) primes.push_back(i);
    }

    vector<ll> mask(N + 1, 0);
    for (ll i = 2; i <= N; i++) {
        ll t = i, m = 0;
        for (int pi = 0; pi < (int)primes.size(); pi++) {
            if (t % primes[pi] == 0) {
                m |= (1LL << pi);
                while (t % primes[pi] == 0) t /= primes[pi];
            }
        }
        mask[i] = m;
    }

    ll best = 1;
    int M = N - 1;
    for (int bm = 1; bm < (1 << M); bm++) {
        ll sum = 1, used = 0;
        bool ok = true;
        for (int i = 0; i < M && ok; i++) {
            if (bm & (1 << i)) {
                ll num = i + 2;
                if (used & mask[num]) ok = false;
                else { used |= mask[num]; sum += num; }
            }
        }
        if (ok && sum > best) best = sum;
    }
    cout << best << "\n";
    return 0;
}
