#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE387: Sum of strong right-truncatable Harshad primes < N
// Harshad: n % digit_sum(n) == 0
// Right-truncatable: truncating last digit always gives Harshad
// Strong: n / digit_sum(n) is prime
// Strong right-truncatable Harshad prime: prime p where p/10 is strong + right-truncatable Harshad

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

ll digit_sum(ll n) {
    ll s = 0;
    while (n) { s += n % 10; n /= 10; }
    return s;
}

void dfs(ll num, ll dsum, ll limit, ll &ans) {
    // num is a right-truncatable Harshad number
    // Try to extend it
    for (int d = 0; d <= 9; d++) {
        ll nxt = num * 10 + d;
        if (nxt >= limit) continue;
        ll ndsum = dsum + d;
        if (nxt % ndsum != 0) continue;
        
        // Check if it's a strong Harshad
        if (is_prime(nxt / ndsum)) {
            // Check if appending digits gives a strong right-truncatable Harshad prime
            for (int last : {1, 3, 7, 9}) {
                ll p = nxt * 10 + last;
                if (p >= limit) continue;
                if (is_prime(p)) ans += p;
            }
        }
        
        // Recurse
        dfs(nxt, ndsum, limit, ans);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    ll ans = 0;
    // Single-digit Harshad numbers: 1-9
    for (ll d = 1; d <= 9; d++) {
        dfs(d, d, N, ans);
    }
    
    cout << ans << "\n";
    return 0;
}
