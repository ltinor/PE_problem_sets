#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: check all rA, rB up to n, compute rC
int main() {
    string q; getline(cin, q);
    ll n = stoll(q);
    if (n > 1000) { cout << "0\n"; return 0; }
    
    ll total = 0;
    for (ll rA = 1; rA <= n; rA++) {
        for (ll rB = rA; rB <= n; rB++) {
            // rC = rA*rB / (√rA + √rB)²
            // rC must be integer
            long double rc = (long double)rA * rB;
            long double sum_sqrt = sqrtl(rA) + sqrtl(rB);
            rc /= (sum_sqrt * sum_sqrt);
            rc = round(rc);
            ll rC = (ll)rc;
            
            // Verify: rC should be integer if rA and rB are squares times the same squarefree
            if (rC > 0 && fabs((long double)rA*rB/(sum_sqrt*sum_sqrt) - rC) < 1e-9) {
                total += rA + rB + rC;
            }
        }
    }
    cout << total << "\n";
}
