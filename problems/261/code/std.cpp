#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// Pell-based solution for square-pivot sum
// Equation: (m+1)k(k-m) = mn(n+m+1)
// Transform: X=2k-m, Y=2n+m+1 => mY²-(m+1)X²=m(m+1)
// Let X=mt => Y²=(m+1)(mt²+1)
// Recurrence: (Y,t) -> multiply by unit (2m+1,2) of Y²-m(m+1)t²=1

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    unordered_set<ll> pivots;
    
    // m=1..sqrt(N/2) (since first nontrivial k=2m(m+1) <= N)
    ll mmax = (ll)sqrt(N / 2) + 5;
    
    for (ll m = 1; m <= mmax && m <= N; m++) {
        ll Y = m + 1;  // fundamental solution
        ll t = 1;
        
        while (true) {
            // k = m*(t+1)/2 (t is always odd, so t+1 even)
            ll k = m * (t + 1) / 2;
            if (k > N) break;
            
            // n = (Y - m - 1) / 2
            ll n = (Y - m - 1) / 2;
            
            if (n >= k) {
                pivots.insert(k);
            }
            
            // Advance via Pell unit (2m+1, 2)
            ll nextY = (2*m + 1) * Y + 2 * m * (m + 1) * t;
            ll nextt = 2 * Y + (2*m + 1) * t;
            
            // Check overflow
            if (nextY < Y || nextt < t) break;
            
            Y = nextY;
            t = nextt;
        }
    }
    
    // Sum all distinct pivots
    ull ans = 0;
    for (ll k : pivots) {
        ans += k;
    }
    
    cout << ans << "\n";
    return 0;
}
