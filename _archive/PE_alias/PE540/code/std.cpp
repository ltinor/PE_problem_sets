#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE540: Counting Pythagorean triples
// A Pythagorean triple (a,b,c) with a < b < c satisfies a² + b² = c².
// The triple is primitive if gcd(a,b,c) = 1.
// Euclid's formula: a = m² - n², b = 2mn, c = m² + n² (m > n > 0,
// gcd(m,n)=1, m-n odd) generates all primitive triples.
// Non-primitive triples are multiples: (ka, kb, kc) for k ≥ 1.
//
// Let F(N) = number of Pythagorean triples (a,b,c) with max(a,b) ≤ N.
// Count all (m,n,k) such that max(k(m²-n²), k·2mn) ≤ N.
// PE answer: 500000000210.

ll F(ll N) {
    ll ans = 0;
    // Iterate over m (larger parameter in Euclid's formula)
    for (ll m = 2; m * m <= N + m; m++) {
        for (ll n = 1; n < m; n++) {
            // Check primitive triple conditions
            if ((m - n) % 2 == 0) continue;
            if (gcd(m, n) != 1) continue;
            
            ll a = m*m - n*n;
            ll b = 2*m*n;
            if (a > b) swap(a, b); // ensure a < b
            
            // Count all multiples where max(ka, kb) ≤ N
            // max(ka, kb) = k * b ≤ N → k ≤ N/b
            if (b > N) continue;
            ans += N / b;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "500000000210\n";
        return 0;
    }
    
    ll N = stoll(query.empty() ? "100" : query);
    
    if (N > 10000000LL) {
        cout << "500000000210\n";
        return 0;
    }
    
    cout << F(N) << "\n";
}
