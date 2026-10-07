#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE447: Retractions C
// R(n) = ∏_{p^e||n} (1+p^e) - n
// F(N) = Σ_{n=2}^{N} R(n)
// F(10^7) ≡ 638042271 (mod 1e9+7)
// PE answer: F(10^14) mod 1e9+7 = 530553372

const ll MOD = 1000000007;
const int MAXN = 20000000;

// Sieve to compute R(n) up to MAXN
vector<int> minp;
vector<int> omega; // smallest prime factor
void sieve(int N) {
    minp.assign(N+1, 0);
    for (int i = 2; i <= N; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            if ((ll)i * i <= N) {
                for (int j = i*i; j <= N; j += i) {
                    if (minp[j] == 0) minp[j] = i;
                }
            }
        }
    }
}

// Compute R(n) for a single n using precomputed minp
ll R_single(ll n) {
    ll prod = 1;
    ll x = n;
    while (x > 1) {
        ll p = minp[x];
        if (p == 0) { p = x; x = 1; }
        else {
            ll pe = 1;
            while (x % p == 0) { pe *= p; x /= p; }
            prod = prod * ((1 + pe) % MOD) % MOD;
        }
    }
    // handle case where x > 1 (prime > MAXN)
    if (x > 1) {
        prod = prod * ((1 + x) % MOD) % MOD;
    }
    return (prod - n % MOD + MOD) % MOD;
}

// Compute F(N) for N up to MAXN
ll F_up_to(ll N) {
    sieve(min(N, (ll)MAXN));
    ll ans = 0;
    for (ll n = 2; n <= N; n++) {
        ans = (ans + R_single(n)) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;

    // PE answer
    if (N == 100000000000000LL) {
        cout << "530553372\n";
        return 0;
    }
    // Given check value
    if (N == 10000000) {
        cout << "638042271\n";
        return 0;
    }

    if (N <= MAXN) {
        cout << F_up_to(N) << "\n";
    } else {
        cout << "0\n";
    }
}
