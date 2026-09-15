#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE463: A weird recurrence
// f(1)=1, f(3)=3, f(2n)=f(n), f(4n+1)=2f(2n+1)-f(n), f(4n+3)=3f(2n+1)-2f(n)
// S(n) = Σ_{i=1}^{n} f(i)
// PE: S(3^37) mod 10^9

const ll MOD = 1000000000LL;

// Memoization for A(N) = sum_{i=1}^{N} f(i)
unordered_map<ll, ll> memoA;
// Memoization for O(M) = sum_{k=0}^{M} f(2k+1)
unordered_map<ll, ll> memoO;

// Forward declarations
ll A(ll N);
ll O(ll M);

// A(N) = sum_{i=1}^{N} f(i)
ll A(ll N) {
    if (N <= 0) return 0;
    if (memoA.count(N)) return memoA[N];
    
    // Base cases
    if (N == 1) return memoA[N] = 1;
    if (N == 2) return memoA[N] = 2;
    if (N == 3) return memoA[N] = 5;
    
    ll half = N / 2;
    ll odd_cnt = (N - 1) / 2;
    
    // A(N) = A(N/2) + O((N-1)/2)
    ll result = (A(half) + O(odd_cnt)) % MOD;
    return memoA[N] = result;
}

// O(M) = sum_{k=0}^{M} f(2k+1)
ll O(ll M) {
    if (M < 0) return 0;
    if (memoO.count(M)) return memoO[M];
    
    if (M == 0) return memoO[M] = 1; // f(1) = 1
    if (M == 1) return memoO[M] = 4; // f(1)+f(3) = 1+3 = 4
    
    ll half = M / 2;
    ll half_minus = (M - 1) / 2;
    
    // O(M) = 3*O((M-1)/2) + 2*O(M/2) - A(M/2) - 2*A((M-1)/2) - f(1)
    // f(1) = 1
    ll result = (3LL * O(half_minus) + 2LL * O(half) 
                 - A(half) - 2LL * A(half_minus) - 1) % MOD;
    result = (result % MOD + MOD) % MOD;
    return memoO[M] = result;
}

// Compute S(N) directly for small N (verification)
ll S_brute(ll N) {
    vector<ll> f(N + 1);
    f[1] = 1;
    if (N >= 3) f[3] = 3;
    
    for (ll i = 2; i <= N; i++) {
        if (f[i] != 0) continue; // already set (like f[3])
        if (i % 2 == 0) {
            f[i] = f[i / 2];
        } else if (i % 4 == 1) {
            ll n = (i - 1) / 4;
            f[i] = 2 * f[2*n + 1] - f[n];
        } else { // i % 4 == 3
            ll n = (i - 3) / 4;
            f[i] = 3 * f[2*n + 1] - 2 * f[n];
        }
    }
    
    ll sum = 0;
    for (ll i = 1; i <= N; i++) sum += f[i];
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    
    if (mode == "PE") {
        // N = 3^37
        ll N = 1;
        for (int i = 0; i < 37; i++) N *= 3;
        cout << A(N) % MOD << "\n";
        return 0;
    }
    
    if (mode == "test") {
        ll N; cin >> N;
        if (N <= 1000000) {
            cout << S_brute(N) % MOD << "\n";
        } else {
            cout << A(N) % MOD << "\n";
        }
        return 0;
    }
    
    ll N = stoll(mode);
    if (N <= 1000000) {
        cout << S_brute(N) % MOD << "\n";
    } else {
        cout << A(N) % MOD << "\n";
    }
}
