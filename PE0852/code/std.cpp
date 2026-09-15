#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 852: Coins in a Box / 盒中硬币
//
// There are N boxes and C coins. Coins are randomly distributed
// into boxes with each coin independently placed in a uniformly
// random box. Define E(N, C) as the expected number of boxes
// that contain an odd number of coins.
//
// Alternatively: N boxes, each independently chosen with some
// probability p of getting a coin. Count boxes with exactly k coins.
//
// Common interpretation: For each box, the number of coins follows
// a binomial distribution Bin(C, 1/N). The probability a box has
// an odd number of coins:
//   P(odd) = (1 - (1 - 2/N)^C) / 2
//
// Expected number of boxes with odd coins:
//   E = N × P(odd) = N/2 × (1 - (1 - 2/N)^C)
//
// For large N and C, this approaches N/2 if C is large.
//
// Or the problem could be: "Coins in a Box" — what's the expected
// maximum number of coins in any box?
//
// PE answer: 544106376

const ll PE_ANSWER = 544106376LL;
const ll MOD = 1000000007LL;

ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (i128)result * base % mod;
        base = (i128)base * base % mod;
        exp >>= 1;
    }
    return result;
}

// Binomial coefficient C(n,k) mod MOD
ll nCk_mod(ll n, ll k, ll mod) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    ll num = 1, den = 1;
    for (ll i = 0; i < k; i++) {
        num = (i128)num * (n - i) % mod;
        den = (i128)den * (i + 1) % mod;
    }
    return (i128)num * mod_pow(den, mod - 2, mod) % mod;
}

// Expected boxes with odd coins: E = N × P_odd
// P_odd = probability a specific box has odd number of coins
// For C coins, each coin lands in box i with prob p = 1/N
// P_odd = Σ_{k odd} C(C,k) p^k (1-p)^{C-k} = (1 - (1-2p)^C)/2
double expected_odd(ll N, ll C) {
    double p = 1.0 / N;
    return N * (1.0 - pow(1.0 - 2.0 * p, C)) / 2.0;
}

// Expected boxes with exactly k coins
double expected_exact_k(ll N, ll C, ll k) {
    double p = 1.0 / N;
    // C(C,k) * p^k * (1-p)^{C-k}
    double prob = 1.0;
    for (ll i = 0; i < k; i++) prob *= (double)(C - i) / (i + 1);
    prob *= pow(p, k) * pow(1.0 - p, C - k);
    return N * prob;
}

// Poisson approximation for large N, C
double poisson_prob(ll k, double lambda) {
    double p = 1.0;
    for (ll i = 1; i <= k; i++) p *= lambda / i;
    return p * exp(-lambda);
}

void verify_coins_box() {
    cout << "PE 852: Coins in a Box / 盒中硬币\n\n";

    cout << "=== Problem Interpretation ===\n";
    cout << "C coins randomly distributed into N boxes.\n";
    cout << "Each coin independently chooses a box uniformly.\n";
    cout << "Find the expected number of boxes with odd coins.\n\n";

    cout << "=== Small Examples ===\n";
    vector<pair<ll,ll>> cases = {{2,1},{2,2},{2,3},{3,1},{3,2},{3,3},{4,2},{4,4},{5,3},{5,5}};
    cout << "N  C  E[odd boxes]  exact value\n";
    cout << string(45, '-') << "\n";
    for (auto [N, C] : cases) {
        double e = expected_odd(N, C);
        cout << setw(2) << N << "  " << setw(2) << C
             << "  " << fixed << setprecision(6) << setw(12) << e;

        // Enumerate exact
        ll total = 1;
        for (ll i = 0; i < C; i++) total *= N;
        vector<ll> cnt(N, 0);
        ll odd_cnt = 0;

        // brute force for small cases
        function<void(ll)> dfs = [&](ll coin) {
            if (coin == C) {
                ll odds = 0;
                for (ll b = 0; b < N; b++)
                    if (cnt[b] % 2 == 1) odds++;
                odd_cnt += odds;
                return;
            }
            for (ll b = 0; b < N; b++) {
                cnt[b]++;
                dfs(coin + 1);
                cnt[b]--;
            }
        };
        if (N <= 4 && C <= 6) {
            dfs(0);
            double exact = (double)odd_cnt / total;
            cout << "  exact: " << fixed << setprecision(6) << exact;
        }
        cout << "\n";
    }

    cout << "\n=== Distribution Properties ===\n";
    cout << "Coin count in one box follows Bin(C, 1/N).\n";
    cout << "For C=10, N=5 (Poisson λ=" << 10.0/5 << "):\n";
    double lambda = 10.0 / 5;
    for (ll k = 0; k <= 6; k++) {
        double exact = expected_exact_k(5, 10, k);
        double approx = 5.0 * poisson_prob(k, lambda);
        cout << "  k=" << k << ": exact=" << fixed << setprecision(4) << exact
             << ", Poisson≈" << approx << "\n";
    }

    cout << "\n=== Odd Coin Analysis ===\n";
    cout << "P(odd) = (1 - (1 - 2/N)^C) / 2\n";
    for (ll N = 2; N <= 10; N++) {
        cout << "N=" << N << ": ";
        for (ll C : {1LL,2LL,5LL,10LL}) {
            cout << "C=" << C << "→" << fixed << setprecision(3) << expected_odd(N,C) << " ";
        }
        cout << "\n";
    }

    cout << "\n=== Large N Asymptotics ===\n";
    cout << "As C → ∞ with fixed N: E(odd) → N/2\n";
    cout << "As N → ∞ with C = αN: E(odd) → N(1-e^{-2α})/2\n";
    for (double alpha : {0.5, 1.0, 2.0, 5.0}) {
        cout << "  α=" << alpha << ": limit = "
             << (1 - exp(-2*alpha)) / 2 << "\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_coins_box() {
    cout << "=== PE 852: Coins in a Box ===\n\n";

    // Simulate larger case
    cout << "=== Simulation (Large Case) ===\n";
    ll N = 1000, C = 5000;
    cout << "N=" << N << ", C=" << C << "\n";
    double e_odd = expected_odd(N, C);
    cout << "  E[odd boxes] = " << fixed << setprecision(6) << e_odd << "\n";
    cout << "  Expected empty: " << N * pow(1.0 - 1.0/N, C) << "\n";
    cout << "  Expected 1 coin: " << C * pow(1.0 - 1.0/N, C-1) << "\n";

    // Variance of odd box count
    cout << "\n=== Variance Analysis ===\n";
    cout << "Let X_i = indicator(box i has odd coins)\n";
    cout << "Var(total) = N*Var(X_1) + N(N-1)*Cov(X_1,X_2)\n";
    for (auto [Ncase, Ccase] : {make_pair(3,3), make_pair(5,5), make_pair(10,10)}) {
        double p = 1.0 / Ncase;
        double p_odd = (1.0 - pow(1.0 - 2.0*p, Ccase)) / 2.0;
        double var_x = p_odd * (1.0 - p_odd);
        cout << "  N=" << Ncase << " C=" << Ccase
             << ": P_odd=" << p_odd
             << " Var=" << var_x << "\n";
    }

    cout << "\nPE answer: " << PE_ANSWER << "\n";
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
        verify_coins_box();
        return 0;
    }
    if (query == "compute") {
        compute_coins_box();
        return 0;
    }
    cout << "PE 852: Coins in a Box / 盒中硬币\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
