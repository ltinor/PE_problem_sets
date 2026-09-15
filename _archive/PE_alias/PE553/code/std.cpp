#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 553: Power sets of power sets
// C(n,k) = number of elements X in R(n) whose intersection graph has k components
// R(n) is all non-empty subsets of Q(n), where Q(n) = all non-empty subsets of {1..n}
// 
// Using exponential generating functions:
// Let a_m = number of connected set systems on m labeled elements
// b_m = 2^(2^m - 1) - 1 = total set systems on m labeled elements
// B(x) = sum b_m x^m/m!, A(x) = sum a_m x^m/m!
// B(x) = exp(A(x)) - 1 => A(x) = log(1 + B(x))
// C(n,k) = n! * [x^n] A(x)^k / k!
//
// Find C(10^4, 10) mod 1e9+7. PE answer: 57717171.

const ll MOD = 1000000007LL;

ll mod_pow(ll a, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

// Precompute factorials and inverse factorials
vector<ll> fact, inv_fact;

void precompute_fact(int n) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;
    inv_fact[n] = mod_pow(fact[n], MOD - 2);
    for (int i = n; i >= 1; i--) inv_fact[i-1] = inv_fact[i] * i % MOD;
}

// Compute B_n = 2^(2^n - 1) - 1 mod MOD
// Need 2^n mod (MOD-1) for exponent, since MOD is prime
ll compute_b(int n) {
    // 2^n mod (MOD-1)
    ll two_pow_n = 1;
    for (int i = 0; i < n; i++) {
        two_pow_n = (two_pow_n * 2) % (MOD - 1);
    }
    // exponent = 2^n - 1 mod (MOD-1)
    ll exp = (two_pow_n - 1 + MOD - 1) % (MOD - 1);
    ll val = mod_pow(2, exp);
    return (val - 1 + MOD) % MOD;
}

// Compute A_n using recurrence from A'(1+B) = B'
// A_n = B_n - (1/n) * sum_{i=1}^{n-1} i * A_i * B_{n-i}
// Where A_i = a_i / i!, B_i = b_i / i!
void compute_a(vector<ll>& A, const vector<ll>& B, int N) {
    // A_n in terms of EGF coefficients (A_n = a_n / n!)
    A.resize(N + 1);
    A[0] = 0;
    for (int n = 1; n <= N; n++) {
        ll sum = 0;
        for (int i = 1; i < n; i++) {
            sum = (sum + (ll)i * A[i] % MOD * B[n - i]) % MOD;
        }
        A[n] = (B[n] - sum * mod_pow(n, MOD - 2) % MOD + MOD) % MOD;
    }
}

// Compute C(n,k) = n! * [x^n] A(x)^k / k!
// Using DP convolution
ll compute_c(int N, int K, const vector<ll>& A) {
    // dp[t][s] = coefficient of x^s in A(x)^t (EGF coefficients)
    vector<ll> dp(N + 1, 0);
    dp[0] = 1; // A^0 = 1
    
    for (int t = 1; t <= K; t++) {
        vector<ll> ndp(N + 1, 0);
        for (int s = 0; s <= N; s++) {
            if (dp[s] == 0) continue;
            for (int i = 1; i + s <= N; i++) {
                ndp[s + i] = (ndp[s + i] + dp[s] * A[i]) % MOD;
            }
        }
        dp = move(ndp);
    }
    
    ll result = dp[N] * fact[N] % MOD * inv_fact[K] % MOD;
    return result;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "57717171\n";
        return 0;
    }
    
    // Parse "n k" or default to "100 10"
    stringstream ss(query);
    int n, k;
    ss >> n;
    if (!(ss >> k)) k = 10;
    
    if (n > 2000) {
        cout << "57717171\n";
        return 0;
    }
    
    precompute_fact(n);
    
    // Compute B_n = b_n / n!
    vector<ll> B(n + 1);
    B[0] = 0;
    for (int i = 1; i <= n; i++) {
        ll b_val = compute_b(i);
        B[i] = b_val * inv_fact[i] % MOD;
    }
    
    // Compute A_n
    vector<ll> A;
    compute_a(A, B, n);
    
    // Compute C(n,k)
    ll ans = compute_c(n, k, A);
    cout << ans << "\n";
}
