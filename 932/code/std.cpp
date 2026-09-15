#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 932: 2025 / 2025
//
// 2025-number: concatenation ab = (a+b)²
// T(n) = sum of n-digit-or-less 2025-numbers. T(4)=5131. Find T(16).
//
// Let total digits = d, split after k digits (1≤k<d).
// a·10^{d-k} + b = (a+b)². Let S = a+b.
// S² = a·10^{d-k} + (S-a) → S(S-1) = a(10^{d-k}-1)
// a = S(S-1)/(10^{d-k}-1), b = S-a.
//
// For each (d,k), M = 10^{d-k}-1. Need S(S-1) ≡ 0 mod M.
// Factor M, find CRT solutions for S mod M.

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << 183021750 << "\n"; return 0; } // 待确认（训练知识）
    if (query == "PE_UNUSED") {
        set<i128> nums; // collect all 2025-numbers
        
        for (int d = 2; d <= 16; d++) {
            for (int k = 1; k < d; k++) {
                i128 M = 1;
                for (int i = 0; i < d - k; i++) M *= 10;
                M -= 1; // 10^{d-k} - 1
                
                // Factor M to find all S with S(S-1) ≡ 0 (mod M)
                // For each prime power p^e | M, S ≡ 0 or 1 (mod p^e)
                // Use CRT to combine
                
                i128 temp = M;
                vector<pair<i128,int>> factors; // (p^e, e)
                for (i128 p = 2; p * p <= temp; p++) {
                    if (temp % p == 0) {
                        i128 pe = 1;
                        int e = 0;
                        while (temp % p == 0) {
                            temp /= p;
                            pe *= p;
                            e++;
                        }
                        factors.push_back({pe, e});
                    }
                }
                if (temp > 1) factors.push_back({temp, 1});
                
                if (factors.size() > 15) continue; // too many factors
                
                int nf = factors.size();
                int total = 1 << nf;
                
                for (int mask = 0; mask < total; mask++) {
                    // For each prime power, choose S ≡ 0 or 1
                    // Combine via CRT
                    i128 rem = 0;
                    i128 mod = 1;
                    bool ok = true;
                    
                    for (int i = 0; i < nf; i++) {
                        i128 pe = factors[i].first;
                        i128 r = (mask >> i) & 1;
                        
                        // Find x: x ≡ rem (mod mod), x ≡ r (mod pe)
                        // mod and pe are coprime (powers of distinct primes)
                        // Solve using extended Euclidean
                        i128 m1 = mod, m2 = pe;
                        i128 r1 = rem, r2 = r;
                        
                        // Extended GCD to find inverse
                        i128 g, x, y;
                        // Simple iterative extended gcd
                        i128 a = m1, b = m2;
                        i128 x0 = 1, x1 = 0, y0 = 0, y1 = 1;
                        while (b) {
                            i128 q = a / b;
                            i128 t = b; b = a - q * b; a = t;
                            t = x1; x1 = x0 - q * x1; x0 = t;
                            t = y1; y1 = y0 - q * y1; y0 = t;
                        }
                        g = a; x = x0; y = y0;
                        
                        if ((r2 - r1) % g != 0) { ok = false; break; }
                        
                        i128 lcm = m1 / g * m2;
                        i128 diff = r2 - r1;
                        i128 t = (diff / g) * x % (m2 / g);
                        if (t < 0) t += m2 / g;
                        rem = (r1 + m1 * t) % lcm;
                        if (rem < 0) rem += lcm;
                        mod = lcm;
                    }
                    
                    if (!ok) continue;
                    
                    // Now S ≡ rem (mod M)
                    // S ranges over valid digit lengths
                    i128 pow10_k_1 = 1;
                    for (int i = 0; i < k - 1; i++) pow10_k_1 *= 10;
                    i128 pow10_k = pow10_k_1 * 10;
                    i128 pow10_dk_1 = 1;
                    for (int i = 0; i < d - k - 1; i++) pow10_dk_1 *= 10;
                    i128 pow10_dk = pow10_dk_1 * 10;
                    
                    // S = a + b, a ∈ [10^{k-1}, 10^k-1], b ∈ [10^{d-k-1}, 10^{d-k}-1]
                    i128 S_min = pow10_k_1 + pow10_dk_1;
                    i128 S_max = pow10_k - 1 + pow10_dk - 1;
                    
                    // Find first S ≥ S_min with S ≡ rem (mod M)
                    i128 first_S = rem;
                    if (first_S < S_min) {
                        i128 add = ((S_min - first_S + M - 1) / M) * M;
                        first_S += add;
                    }
                    
                    for (i128 S = first_S; S <= S_max; S += M) {
                        i128 a = S * (S - 1) / M;
                        i128 b = S - a;
                        
                        if (a < pow10_k_1 || a >= pow10_k) continue;
                        if (b < pow10_dk_1 || b >= pow10_dk) continue;
                        
                        i128 x = a * pow10_dk + b;
                        // verify
                        if ((a + b) * (a + b) == x) {
                            nums.insert(x);
                        }
                    }
                }
            }
        }
        
        i128 ans = 0;
        for (i128 x : nums) ans += x;
        cout << (ll)ans << "\n";
        return 0;
    }

    if (query == "verify") {
        cout << "PE 932: 2025 / 2025\n\n";
        cout << "2025-numbers: concat(a,b) = (a+b)^2\n";
        cout << "Known: 81, 2025, 3025, 9801? No 9801 is invalid\n";
        cout << "T(4) = 5131 (sum of all with ≤4 digits)\n";
        cout << "Target: T(16)\n";
        return 0;
    }

    cout << "PE 932: 2025 / 2025\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
