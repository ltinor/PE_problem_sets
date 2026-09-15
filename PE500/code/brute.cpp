#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Brute force for PE500: find smallest n with given number of divisors
// Only feasible for very small K

int main() {
    string query;
    getline(cin, query);
    ll K = stoll(query);
    
    if (K > 5) {
        cout << "0\n";
        return 0;
    }
    
    ll target = 1LL << K; // 2^K divisors
    
    // Search for smallest n with exactly target divisors
    for (ll n = 1; ; n++) {
        ll divs = 0;
        for (ll d = 1; d * d <= n; d++) {
            if (n % d == 0) {
                divs++;
                if (d * d != n) divs++;
            }
        }
        if (divs == target) {
            cout << n % 500500507LL << "\n";
            return 0;
        }
    }
}
