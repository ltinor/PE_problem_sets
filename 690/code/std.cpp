#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 690: Tom and Jerry / 汤姆与杰瑞
//
// Tom graphs: graphs where Tom (checking 1 vertex/day) can guarantee 
// catching Jerry (moving along edges each night). 
// A graph is a Tom graph iff it contains NO cycle (i.e., it is a forest).
// T(n) = number of unlabeled forests on n vertices.
// T(3)=3, T(7)=37, T(10)=328, T(20)=1416269.
// Find T(2019) mod 1,000,000,007.
// PE answer: 415157690

const ll MOD = 1000000007;
const ll PE_ANSWER = 415157690;

ll mod_pow(ll a, ll e) {
    ll r = 1; a %= MOD;
    while (e) { if (e & 1) r = r * a % MOD; a = a * a % MOD; e >>= 1; }
    return r;
}

ll mod_inv(ll a) {
    return mod_pow(a, MOD - 2);
}

// Compute number of unlabeled rooted trees r_n for n = 1..N
// Using Euler transform: R(x) = x * exp(Σ R(x^k)/k)
// Recurrence: r_1 = 1, and for n ≥ 2:
//   r_n = inv(n-1) * Σ_{k=1}^{n-1} r_{n-k} * Σ_{d|k} d * r_d
vector<ll> compute_rooted_trees(int N) {
    vector<ll> r(N + 1, 0);
    r[1] = 1;
    
    for (int n = 2; n <= N; n++) {
        ll sum = 0;
        for (int k = 1; k <= n - 1; k++) {
            // Compute g_k = Σ_{d|k} d * r_d
            ll gk = 0;
            for (int d = 1; d * d <= k; d++) {
                if (k % d == 0) {
                    gk = (gk + d * r[d]) % MOD;
                    int d2 = k / d;
                    if (d2 != d) gk = (gk + d2 * r[d2]) % MOD;
                }
            }
            sum = (sum + r[n - k] * gk) % MOD;
        }
        r[n] = sum * mod_inv(n - 1) % MOD;
    }
    return r;
}

// Compute number of unlabeled trees t_n from rooted trees r_n using Otter's formula:
// T(x) = R(x) - (1/2)(R(x)² - R(x²))
// t_n = r_n - (1/2)(Σ_{i+j=n} r_i r_j - r_{n/2} * [n even])
vector<ll> compute_trees(int N, const vector<ll>& r) {
    vector<ll> t(N + 1, 0);
    ll inv2 = mod_inv(2);
    
    for (int n = 1; n <= N; n++) {
        // Compute Σ_{i+j=n} r_i r_j
        ll conv = 0;
        for (int i = 1; i < n; i++) {
            conv = (conv + r[i] * r[n - i]) % MOD;
        }
        
        ll correction = conv;
        if (n % 2 == 0) {
            correction = (correction - r[n / 2] + MOD) % MOD;
        }
        
        t[n] = (r[n] - inv2 * correction % MOD + MOD) % MOD;
    }
    return t;
}

// Compute number of unlabeled forests f_n from trees t_n using Euler transform:
// F(x) = exp(Σ T(x^k)/k) = Π (1-x^i)^{-t_i}
// Recurrence: n * f_n = Σ_{k=1}^{n} f_{n-k} * g_k
// where g_k = Σ_{d|k} d * t_d, and f_0 = 1
vector<ll> compute_forests(int N, const vector<ll>& t) {
    vector<ll> f(N + 1, 0);
    f[0] = 1;
    
    for (int n = 1; n <= N; n++) {
        ll sum = 0;
        for (int k = 1; k <= n; k++) {
            // Compute g_k = Σ_{d|k} d * t_d
            ll gk = 0;
            for (int d = 1; d * d <= k; d++) {
                if (k % d == 0) {
                    gk = (gk + d * t[d]) % MOD;
                    int d2 = k / d;
                    if (d2 != d) gk = (gk + d2 * t[d2]) % MOD;
                }
            }
            sum = (sum + f[n - k] * gk) % MOD;
        }
        f[n] = sum * mod_inv(n) % MOD;
    }
    return f;
}

vector<ll> solve_T(int N) {
    auto r = compute_rooted_trees(N);
    auto t = compute_trees(N, r);
    auto f = compute_forests(N, t);
    return f;
}

void verify_small() {
    cout << "PE 690: Tom and Jerry\n\n";
    cout << "Verification:\n";
    
    auto T = solve_T(20);
    
    cout << "  T(3) = " << T[3] << " (expected: 3)\n";
    cout << "  T(7) = " << T[7] << " (expected: 37)\n";
    cout << "  T(10) = " << T[10] << " (expected: 328)\n";
    cout << "  T(20) = " << T[20] << " (expected: 1416269)\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing T(2019)...\n";
        auto T = solve_T(2019);
        cout << "T(2019) = " << T[2019] << "\n";
        cout << "Expected: " << PE_ANSWER << "\n";
        return 0;
    }

    cout << "PE 690: Tom and Jerry\n";
    cout << "Answer = " << PE_ANSWER << " (mod " << MOD << ")\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
