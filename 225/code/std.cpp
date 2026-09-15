#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Tribonacci: T1=T2=T3=1, Tn = Tn-1 + Tn-2 + Tn-3
// Find the K-th odd number that does NOT divide any term

bool is_non_divisor(ll n) {
    // Compute Tribonacci mod n until we find 0 or detect a cycle
    ll a = 1 % n, b = 1 % n, c = 1 % n;

    if(a == 0 || b == 0 || c == 0) return false;

    // Use set to detect cycles. Pack (a,b,c) into a single 64-bit value.
    // n <= ~50000, so n^2 <= 2.5e9, n^3 fits in 64-bit
    unordered_set<ll> seen;
    seen.insert(a * n * n + b * n + c);

    // Maximum steps: at most n^3 states, but bound to prevent hanging
    ll max_steps = min((ll)1e7, n * n * n);
    for(ll step = 0; step < max_steps; step++) {
        ll next = (a + b + c) % n;
        if(next == 0) return false;
        a = b;
        b = c;
        c = next;
        ll state = a * n * n + b * n + c;
        if(seen.count(state)) return true; // cycle, no zero
        seen.insert(state);
    }
    // If we hit max_steps without finding zero and without cycle detection,
    // conservatively assume it IS a divisor to avoid false positives
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    ll cnt = 0;
    for(ll n = 1; ; n += 2) {
        if(is_non_divisor(n)) {
            cnt++;
            if(cnt == K) {
                cout << n << "\n";
                return 0;
            }
        }
    }

    return 0;
}
