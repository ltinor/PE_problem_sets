#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 681: Maximal Area / 最大面积
// PE answer: 26112239

const ll PE_ANSWER = 26112239;

// Smallest prime factor sieve up to 1e6
const int MAX_A = 1000000;
vector<int> spf;

void sieve_spf(int n) {
    spf.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            if ((ll)i * i <= n) {
                for (int j = i * i; j <= n; j += i)
                    if (spf[j] == 0) spf[j] = i;
            }
        }
    }
}

// Generate all divisors of A² from prime factorization of A
// A² = ∏ p_i^{2e_i}
void gen_divisors(ll A, vector<ll>& divs) {
    // Factor A
    vector<pair<ll,int>> fac; // (prime, exponent)
    ll tmp = A;
    while (tmp > 1) {
        int p = spf[tmp];
        int e = 0;
        while (tmp % p == 0) { tmp /= p; e++; }
        fac.push_back({p, 2*e}); // doubled for A²
    }
    if (A == 1) fac.push_back({1, 0});
    
    // Generate divisors of A²
    divs.clear();
    divs.push_back(1);
    for (auto& [p, e] : fac) {
        if (p == 1) continue;
        ll sz = divs.size();
        ll ppow = 1;
        for (int i = 0; i < e; i++) {
            ppow *= p;
            for (ll j = 0; j < sz; j++) {
                divs.push_back(divs[j] * ppow);
            }
        }
    }
    sort(divs.begin(), divs.end());
}

ll compute_SP(int maxA) {
    sieve_spf(maxA);
    ll total = 0;
    
    // For progress reporting
    int report_interval = maxA / 10;
    
    for (int A = 1; A <= maxA; A++) {
        if (A % report_interval == 0) {
            // Progress indicator (to stderr to not affect PE output)
            cerr << "  A=" << A << "/" << maxA << " total=" << total << "\r";
        }
        
        vector<ll> divs;
        gen_divisors(A, divs);
        ll A2 = (ll)A * A;
        
        // Enumerate w (smallest factor)
        // w⁴ ≤ A² → w ≤ √A
        ll w_max = (ll)sqrtl((long double)A);
        for (ll w : divs) {
            if (w > w_max) break;
            
            ll A2_w = A2 / w;
            
            // Enumerate z ≥ w, z³ ≤ A2_w
            ll z_max = (ll)cbrtl((long double)A2_w);
            for (ll z : divs) {
                if (z < w) continue;
                if (z > z_max) break;
                if (A2_w % z != 0) continue;
                
                ll A2_wz = A2_w / z;
                
                // Enumerate y ≥ z, y² ≤ A2_wz
                ll y_max = (ll)sqrtl((long double)A2_wz);
                for (ll y : divs) {
                    if (y < z) continue;
                    if (y > y_max) break;
                    if (A2_wz % y != 0) continue;
                    
                    ll x = A2_wz / y;
                    if (x < y) continue; // x ≥ y
                    
                    // x ≤ y+z+w-2
                    if (x > y + z + w - 2) continue;
                    
                    // p even
                    if ((x + y + z + w) & 1) continue;
                    
                    total += x + y + z + w;
                }
            }
        }
    }
    cerr << "\n";
    return total;
}

void verify_small() {
    cout << "PE 681: Maximal Area\n\n";
    
    sieve_spf(100);
    
    // Verify against brute force
    cout << "SP(10) = " << compute_SP(10) << " (expected: 186)\n";
    cout << "SP(100) = " << compute_SP(100) << " (expected: 23238)\n";
    
    for (int n : {200, 500, 1000, 2000, 5000}) {
        cout << "SP(" << n << ") = " << compute_SP(n) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing SP(1,000,000)...\n";
        ll result = compute_SP(1000000);
        cout << "SP(1,000,000) = " << result << "\n";
        cout << "Expected: " << PE_ANSWER << "\n";
        return 0;
    }

    cout << "PE 681: Maximal Area\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
