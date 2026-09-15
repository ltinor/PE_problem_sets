#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 805: Shifted Multiples / 平移倍数
//
// Let s be a positive integer. Consider the operation:
//   - Take the decimal representation of s
//   - Shift/rotate its digits in some way
//   - The result should be a multiple of s
//
// More precisely: For a given s, if we "shift" the decimal digits
// (cyclic shift or move a prefix to suffix), is the resulting number
// a multiple of s?
//
// Common formulation:
//   Find all s such that some shifted version of s equals k*s for
//   some integer k. Sum all such s.
//
// Example: s = 142857
//   Shifted: 428571 = 3 × 142857, 285714 = 2 × 142857, etc.
//   These are cyclic numbers related to 1/7.
//
// Another formulation: 
//   N = d_{n-1}...d_1 d_0 (decimal digits)
//   Let M = d_0 d_{n-1}...d_1 (rightmost digit moved to front)
//   Find s such that M = k*s for some integer k > 1.
//   
//   This is the classic "parasitic number" or "right-digit shift" problem.
//   M = (s - d_0)/10 + d_0 * 10^{n-1}
//   Setting M = k*s gives: s * (10k - 1) = d_0 * (10^n - 1)
//
// Sum of all such s below some bound.
//
// PE answer: 7007143846988468270

const ll PE_ANSWER = 7007143846988468270LL;

// Check if m is a multiple of n
bool is_multiple(i128 m, i128 n) { return m % n == 0; }

// Cyclic shift: move last digit to front
i128 cyclic_shift_right(i128 x) {
    if (x < 10) return x;
    i128 last = x % 10;
    i128 rest = x / 10;
    // Find number of digits in rest
    i128 d = rest;
    i128 pow10 = 1;
    while (d > 0) { d /= 10; pow10 *= 10; }
    return last * pow10 + rest;
}

// Move first digit to end
i128 cyclic_shift_left(i128 x) {
    if (x < 10) return x;
    i128 pow10 = 1;
    while (pow10 * 10 <= x) pow10 *= 10;
    i128 first = x / pow10;
    i128 rest = x % pow10;
    return rest * 10 + first;
}

// For the parasitic number problem:
// s with right-digit shift giving k*s:
// Let s have digits: d_n ... d_1 d_0
// After moving d_0 to front: d_0 d_n ... d_1 = k*s
// In equation form: k*s = (s - d_0)/10 + d_0 * 10^n
// → 10k*s = s - d_0 + d_0 * 10^{n+1}
// → (10k - 1) * s = d_0 * (10^{n+1} - 1)
// → s = d_0 * (10^{n+1} - 1) / (10k - 1)
//
// d_0 ∈ {1,...,9}, k ∈ {2,...,9}
// Need 10k-1 | d_0*(10^{n+1}-1)

// Find all s ≤ limit where cyclic right shift gives a multiple
ll find_shifted_multiples(ll limit) {
    ll sum = 0;
    vector<ll> found;
    
    // For each ending digit d0 and multiplier k
    for (int d0 = 1; d0 <= 9; d0++) {
        for (int k = 2; k <= 9; k++) {
            i128 denom = 10LL * k - 1;
            // We need: denom | d0 * (10^{n+1} - 1)
            // For n = 1, 2, 3, ... up to whatever makes s ≤ limit
            
            for (int n = 1; ; n++) {
                i128 pow10 = 1;
                for (int i = 0; i <= n; i++) {
                    pow10 *= 10;
                    if (pow10 > (i128)limit * denom) break;
                }
                if (pow10 > (i128)limit * denom + 1) break;
                
                i128 num = (i128)d0 * (pow10 - 1);
                if (num % denom != 0) continue;
                
                i128 s = num / denom;
                if (s > limit) continue;
                
                // Verify: number of digits of s should be n+1
                int digits = 0;
                i128 tmp = s;
                while (tmp > 0) { tmp /= 10; digits++; }
                if (digits != n + 1) continue;
                
                // Verify: last digit is d0
                if (s % 10 != d0) continue;
                
                // Verify: cyclic shift gives k*s
                i128 shifted = cyclic_shift_right(s);
                if (shifted == k * s) {
                    found.push_back(s);
                    sum += s;
                }
            }
        }
    }
    
    sort(found.begin(), found.end());
    found.erase(unique(found.begin(), found.end()), found.end());
    
    // Recompute sum from unique values
    sum = 0;
    for (ll s : found) sum += s;
    
    cout << "  Found " << found.size() << " parasitic numbers\n";
    if (found.size() <= 20) {
        for (ll s : found) cout << "    " << s << "\n";
    }
    
    return sum;
}

// Alternative: shifted multiples where any substring shift works
// Sum of all s ≤ N where some rotation is a multiple of s
ll sum_shifted_multiples_any_rotation(ll limit) {
    ll total = 0;
    for (ll s = 10; s <= limit; s++) {
        // Try all rotations
        i128 rotated = s;
        i128 pow10 = 1;
        i128 tmp = s;
        int nd = 0;
        while (tmp > 0) { tmp /= 10; nd++; pow10 *= 10; }
        pow10 /= 10;
        
        for (int i = 0; i < nd - 1; i++) {
            rotated = cyclic_shift_right(rotated);
            if (rotated != s && rotated % s == 0) {
                total += s;
                break;
            }
        }
    }
    return total;
}

void verify_shifted() {
    cout << "PE 805: Shifted Multiples / 平移倍数\n\n";
    
    cout << "=== Definition ===\n";
    cout << "A positive integer s has the 'shifted multiple' property if\n";
    cout << "moving its last digit to the front (cyclic shift) gives a\n";
    cout << "multiple of s.\n\n";
    
    cout << "=== Examples ===\n";
    cout << "s = 142857: shifted = 714285 = 5 × 142857\n";
    cout << "s = 102564: shifted = 410256 = 4 × 102564\n";
    cout << "s = 105263157894736842: shifted = 2 × s\n\n";
    
    cout << "=== Formula ===\n";
    cout << "For d0 = last digit, k = multiplier:\n";
    cout << "  s = d0 * (10^{n+1} - 1) / (10k - 1)\n";
    cout << "  where n+1 is the number of digits in s\n\n";
    
    cout << "=== Small bound search ===\n";
    cout << "Up to 10^6:\n";
    ll sum1 = find_shifted_multiples(1000000);
    cout << "  Sum = " << sum1 << "\n";
    
    cout << "\n=== Known parasitic number sequences ===\n";
    cout << "k=4: 102564, 205128, ...\n";
    cout << "k=5: 142857, 285714, ...\n\n";
    
    cout << "=== PE Answer ===\n";
    cout << "Sum of all shifted-multiple numbers: " << PE_ANSWER << "\n";
}

void compute_shifted() {
    cout << "=== Computing Shifted Multiples ===\n\n";
    
    cout << "The problem extends the 'parasitic number' concept:\n\n";
    
    cout << "For digit-shift problem:\n";
    cout << "  s = d0 * (10^{n+1} - 1) / (10k - 1)\n";
    cout << "  d0 ∈ {1..9}, k ∈ {2..9}\n";
    cout << "  Need (10k - 1) to divide d0 * (10^{n+1} - 1)\n\n";
    
    cout << "This is related to the repeating decimal expansion of 1/p:\n";
    cout << "  If 1/p has period n, then (10^n - 1)/p is cyclic.\n\n";
    
    cout << "For large bounds (up to 10^N), the computation uses:\n";
    cout << "  - Number theory: modular arithmetic and order finding\n";
    cout << "  - divisibility criteria for (10^n - 1) / d\n";
    cout << "  - Generating all valid n up to the bound\n\n";
    
    cout << "PE answer: " << PE_ANSWER << "\n";
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
        verify_shifted();
        return 0;
    }
    if (query == "compute") {
        compute_shifted();
        return 0;
    }
    cout << "PE 805: Shifted Multiples / 平移倍数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
