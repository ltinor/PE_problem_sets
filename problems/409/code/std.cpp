#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE409: Nim extreme
// Consider Nim positions where heap sizes are a subset of {1..n}
// (each heap size ≤ n, all heap sizes distinct).
// Count the number of winning (N) positions for the first player.
// A position is winning iff XOR of heap sizes ≠ 0.
// 
// Number of subsets with XOR = 0: 2^{n - rank} where rank is the
// dimension of {1..n} as vectors over GF(2).
// Winning = 2^n - 2^{n - rank}
//
// rank = floor(log2(n)) + 1 (the number of bits needed to represent n)
// Actually, the rank of {1..n} over GF(2) is the position of the
// highest set bit (0-indexed) + 1 = MSB position + 1.
//
// PE answer: 253223948 (modulo 10^9+7 or 10^9+9?)

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    ll n, MOD;
    cin >> n >> MOD;
    
    // Compute rank: position of highest set bit + 1
    int rank = 0;
    ll t = n;
    while (t > 0) { rank++; t >>= 1; }
    
    // Total subsets = 2^n
    // Losing subsets = 2^{n - rank}
    // Winning = 2^n - 2^{n - rank}
    
    auto modpow = [&](ll base, ll exp) -> ll {
        ll r = 1;
        base %= MOD;
        while (exp) {
            if (exp & 1) r = (r * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return r;
    };
    
    ll total = modpow(2, n);
    ll losing = modpow(2, n - rank);
    ll winning = (total - losing + MOD) % MOD;
    
    cout << winning << "\n";
}
