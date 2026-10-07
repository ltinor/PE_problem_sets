#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// PE 203 — Squarefree Binomial Coefficients
// Compute distinct C(n,k) for rows 0..N, sum those that are squarefree.
// Key insight: all prime factors of C(n,k) are ≤ N, so only check p² for primes p ≤ N.

bool is_squarefree(ll v, const vector<ll>& primes){
    for(ll p : primes){
        ll p2 = p * p;
        if(p2 > v) break;
        if(v % p2 == 0) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // Generate primes up to N
    vector<bool> is_prime(N+1, true);
    vector<ll> primes;
    for(int i = 2; i <= N; i++){
        if(is_prime[i]){
            primes.push_back(i);
            for(int j = i*i; j <= N; j += i) is_prime[j] = false;
        }
    }

    // Generate Pascal's triangle row by row, collect distinct values
    // C[n][k] = C[n-1][k-1] + C[n-1][k]
    set<ll> distinct;

    for(int n = 0; n < N; n++){
        ll val = 1; // C(n,0)
        distinct.insert(val); // 1 is always squarefree
        for(int k = 1; k <= n/2; k++){
            // C(n,k) = C(n,k-1) * (n-k+1) / k
            // Use exact integer arithmetic
            val = val * (n - k + 1) / k;
            distinct.insert(val);
        }
    }

    ll ans = 0;
    for(ll v : distinct){
        if(is_squarefree(v, primes)){
            ans += v;
        }
    }

    cout << ans << "\n";
}
