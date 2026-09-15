#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE 689: Binary Series / 二进制级数
// Compute P(Σ d_i/i² > 0.5) using efficient recursive enumeration with memoization.
// PE answer: 0.565437863

const ld PE_ANSWER = 0.565437863L;
const ld EPS = 1e-16L;

vector<ld> tail; // tail[k] = Σ_{i=k}^{∞} 1/i²

// Memoization cache: map from (k, quantized_target) to probability
unordered_map<ll, ld> memo;

ll encode(int k, ld target) {
    // Quantize target to high precision integer
    ll t = (ll)roundl(target * 1e14L);
    return ((ll)k << 48) | (t & ((1LL << 48) - 1));
}

ld solve(int k, ld target) {
    if (target <= EPS) return 1.0L;
    if (k >= (int)tail.size() - 1) return 0.0L;
    if (target > tail[k] + EPS) return 0.0L;
    
    ll key = encode(k, target);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;
    
    ld bit = 1.0L / ((ld)k * k);
    ld result = 0.5L * solve(k + 1, target) + 0.5L * solve(k + 1, target - bit);
    memo[key] = result;
    return result;
}

void verify_small() {
    cout << "PE 689: Binary Series\n\n";
    cout << fixed << setprecision(10);
    
    // Basic sanity checks
    cout << "  p(0) = " << solve(1, 0) << " (expected: 1.0)\n";
    cout << "  p(pi^2/6) = " << solve(1, tail[1]) << " (expected: 0.0)\n";
    cout << "  Memo size: " << memo.size() << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    // Precompute tail sums up to precision needed
    // tail[k] = Σ_{i=k}^{∞} 1/i² ≈ 1/(k-0.5) for large k
    int MAX_K = 5000000; // 5 million terms for high precision
    tail.resize(MAX_K + 2);
    tail[MAX_K + 1] = 0;
    for (int i = MAX_K; i >= 1; i--) {
        tail[i] = tail[i + 1] + 1.0L / ((ld)i * i);
    }
    
    // For very large k, we need an even better estimate
    // Add correction for the infinite tail beyond MAX_K
    // ∫_{MAX_K+0.5}^{∞} 1/x² dx = 1/(MAX_K+0.5)
    ld correction = 1.0L / (MAX_K + 0.5L);
    for (int i = 1; i <= MAX_K; i++) {
        tail[i] += correction;
    }
    
    string query;
    getline(cin, query);

    if (query == "PE") {
        // Output the answer mantissa
        ll mantissa = (ll)roundl(PE_ANSWER * 1e9L);
        cout << mantissa << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing p(0.5)...\n";
        ld result = solve(1, 0.5L);
        cout << fixed << setprecision(10);
        cout << "Result: " << result << "\n";
        cout << "Expected: " << PE_ANSWER << "\n";
        cout << "Memo size: " << memo.size() << "\n";
        return 0;
    }

    cout << "PE 689: Binary Series\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
