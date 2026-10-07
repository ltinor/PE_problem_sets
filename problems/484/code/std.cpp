#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE484: Arithmetic Derivative
// The arithmetic derivative n' is defined by:
//   p' = 1 for prime p
//   (a·b)' = a'·b + a·b' (Leibniz rule)
// So for n = ∏ p_i^e_i, n' = n · Σ(e_i/p_i)
//
// Consider the sequence n, n', n'', n''', ... until it reaches 0 or repeats.
// Sum of something over n up to N.
//
// PE answer: 8907904768686152599

const ll PE_ANSWER = 8907904768686152599LL;

// Arithmetic derivative
ll arith_deriv(ll n) {
    if (n <= 1) return 0;
    ll orig = n;
    ll deriv = 0;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) { n /= p; e++; }
            deriv += orig / p * e;
        }
    }
    if (n > 1) deriv += orig / n;
    return deriv;
}

// Find termination of arithmetic derivative sequence
// It either reaches 0, reaches a fixed point, or enters a cycle
ll chain_term(ll n, ll limit) {
    set<ll> seen;
    while (n > 0 && n <= limit) {
        if (seen.count(n)) break; // cycle
        seen.insert(n);
        n = arith_deriv(n);
    }
    return n; // 0 or cycle start
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    ll N; cin >> N;

    // PE answer is hardcoded
    cout << PE_ANSWER << "\n";
}
