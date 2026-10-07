#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 200: Find the K-th prime-proof sqube containing "200"
// Answer for K=200: 229161792008
// K ≤ 200

ll mul_mod(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}

ll pow_mod(ll a, ll e, ll mod) {
    ll res = 1;
    a %= mod;
    while (e) {
        if (e & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        e >>= 1;
    }
    return res;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    vector<ll> bases = {2, 3, 5, 7, 11, 13, 17};
    for (ll a : bases) {
        if (a >= n) continue;
        ll x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

bool contains_200(ll n) {
    string s = to_string(n);
    return s.find("200") != string::npos;
}

bool is_prime_proof(ll n) {
    string s = to_string(n);
    int len = s.size();
    for (int i = 0; i < len; i++) {
        char orig = s[i];
        for (char d = '0'; d <= '9'; d++) {
            if (d == orig) continue;
            if (i == 0 && d == '0') continue;
            s[i] = d;
            if (is_prime(stoll(s))) return false;
        }
        s[i] = orig;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    // Generate primes up to 500000 (enough for p up to ~170000)
    const int MAX_PRIME = 500000;
    vector<bool> is_p(MAX_PRIME + 1, true);
    is_p[0] = is_p[1] = false;
    for (int i = 2; i * i <= MAX_PRIME; i++) {
        if (is_p[i]) {
            for (int j = i * i; j <= MAX_PRIME; j += i) is_p[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= MAX_PRIME; i++) {
        if (is_p[i]) primes.push_back(i);
    }

    using Entry = tuple<ll, int, int>; // (value, p_idx, q_idx)
    priority_queue<Entry, vector<Entry>, greater<Entry>> pq;

    // Initialize with many primes to cover all needed squbes
    // Max p needed: sqrt(max_sqube / 2^3) for K≤200
    int init_limit = min((int)primes.size(), 50000);
    for (int i = 0; i < init_limit; i++) {
        ll p = primes[i];
        int j = (i == 0) ? 1 : 0;
        if (j < (int)primes.size()) {
            ll q = primes[j];
            ll val = (ll)p * p * q * q * q;
            if (val > 0) pq.push({val, i, j});
        }
    }

    int next_p = init_limit; // next prime index to add
    int found = 0;
    ll ans = 0;

    while (!pq.empty() && found < K) {
        auto [val, pi, qi] = pq.top();
        pq.pop();

        // Add new primes dynamically if we might need them
        if (next_p < (int)primes.size() && pq.size() < 50000) {
            ll np = primes[next_p];
            int nq_idx = (next_p == 0) ? 1 : 0;
            if (nq_idx < (int)primes.size()) {
                ll nq = primes[nq_idx];
                ll nval = np * np * nq * nq * nq;
                if (nval > 0) pq.push({nval, next_p, nq_idx});
                next_p++;
            }
        }

        // Check conditions
        if (contains_200(val) && is_prime_proof(val)) {
            found++;
            if (found == K) {
                ans = val;
                break;
            }
        }

        // Push next sqube for the same p
        int nq = qi + 1;
        while (nq < (int)primes.size() && primes[nq] == primes[pi]) nq++;
        if (nq < (int)primes.size()) {
            ll p = primes[pi];
            ll q = primes[nq];
            ll nval = (ll)p * p * q * q * q;
            if (nval > 0) pq.push({nval, pi, nq});
        }
    }

    cout << ans << "\n";
}
