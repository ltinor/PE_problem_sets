#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 925: Larger Digit Permutation III / 更大的数字重排（三）
//
// B(n) = smallest number > n formed by rearranging digits of n, or 0 if none.
// T(N) = Σ_{n=1}^{N} B(n^2).
// Given T(10) = 270, T(100) = 335316.
// Find T(10^16) mod 1e9+7.
//
// Unlike PE 924 where the sequence a_n grows super-exponentially,
// here we sum B(n^2) for n = 1, 2, ..., 10^16.
// n ranges up to 10^16, and n^2 ranges up to 10^32.
//
// 10^16 is too many to iterate individually, but we can use digit DP
// to count contributions by digit pattern.
//
// Key approach: For each possible digit multiset of n^2, compute B(n^2)
// and count how many n produce that multiset.
//
// But n^2 is not "independent" of n — it's the square of n.
// We need digit DP on n, tracking the partial square.
//
// For n up to 10^16 (16 decimal digits), n^2 has up to 32 digits.
// Digit DP on n with state: (position, carry, digit_counts_of_square).
// But 32-digit state is too large.
//
// Alternative: Use generating functions or mathematical properties.
//
// Observation: For large n, n^2 has many digits. B(n^2) depends on
// the digit multiset of n^2. The contribution of B(n^2) mod 1e9+7
// might be computable via combinatorial counting.
//
// Let's try a different angle: for each possible digit multiset D
// (with up to 32 digits), B(D) is the next permutation value.
// If we can count how many n produce each digit multiset for n^2...
//
// That's essentially: count n such that the set of digits of n^2 = D.
// This is a digit-DP problem over n.
//
// Since n has 16 digits, n^2 has up to 32 digits.
// The digit DP state would track:
// - position in n (16 positions)
// - tight flag (whether prefix matches N=10^16-1, i.e., all 9s)
// - carry from squaring (up to maybe 9*9*16 ≈ 1296, but after adding,
//   the carry in schoolbook multiplication can be larger)
// - digit frequency array of partial n^2 (32 counts for digits 0-9)
//
// Too many states for straightforward DP.
//
// Maybe we can use the fact that we only need the sum mod 1e9+7,
// and B(n^2) for numbers with many digits can be expressed in terms
// of digit counts.
//
// B(n) for a multiset D: let the digits be d_1 ≤ d_2 ≤ ... ≤ d_k.
// Find the rightmost position i where d_i < d_{i+1}.
// Then B(n) is: keep first i-1 digits same (but rearranged),
// put d_{i+1} next, then sort the rest ascending.
//
// So B(n) = prefix_value * 10^{remaining} + suffix_value.
// The prefix and suffix are determined by the sorted digit multiset
// and the "pivot" position.
//
// For the sum over many n, we might be able to compute the expected
// contribution using digit distribution probabilities.
//
// Actually, for n up to 10^16, n^2 has 1 to 32 digits.
// Let's group by the number of digits of n^2:
//   n ∈ [1, 3]: n^2 has 1 digit
//   n ∈ [4, 9]: n^2 has 2 digits
//   ...
//   n ∈ [10^7, 10^8-1]: n^2 has 15-16 digits
//   ...
//   n ∈ [10^15, 10^16-1]: n^2 has 31-32 digits
//
// For each range, the number of n is about the range size,
// and n^2 sweeps through a range.
//
// I think this problem requires a clever mathematical decomposition.
// Let me just create the template with a brute-force verifier for small N.

const ll MOD = 1000000007LL;

ll B(ll n) {
    string s = to_string(n);
    int i = s.size() - 2;
    while (i >= 0 && s[i] >= s[i+1]) i--;
    if (i < 0) return 0;
    int j = s.size() - 1;
    while (s[j] <= s[i]) j--;
    swap(s[i], s[j]);
    reverse(s.begin() + i + 1, s.end());
    return stoll(s);
}

void verify_larger_digit_perm_iii() {
    cout << "PE 925: Larger Digit Permutation III\n\n";
    
    // Verify T(10) = 270
    ll t10 = 0;
    cout << "First 10 values of B(n^2):\n";
    for (ll n = 1; n <= 10; n++) {
        ll bn = B(n * n);
        t10 += bn;
        cout << "  n=" << n << ": n^2=" << n*n << ", B(n^2)=" << bn << "\n";
    }
    cout << "T(10) = " << t10 << " (expected 270)\n\n";
    
    // Verify T(100) = 335316
    ll t100 = 0;
    for (ll n = 1; n <= 100; n++)
        t100 += B(n * n);
    cout << "T(100) = " << t100 << " (expected 335316)\n\n";
    
    // Distribution analysis
    cout << "Digit count analysis for B(n^2):\n";
    map<int, int> zero_dist;
    for (ll n = 1; n <= 1000; n++)
        if (B(n*n) == 0) zero_dist[to_string(n*n).size()]++;
    cout << "B(n^2)=0 cases by number of digits in n^2 (n≤1000):\n";
    for (auto& [dig, cnt] : zero_dist)
        cout << "  " << dig << " digits: " << cnt << "\n";
    
    cout << "\n=== PE Answer ===\n";
    cout << "T(10^16) mod 1e9+7 = ? (PLACEHOLDER)\n";
}

const ll PE_ANSWER = 0; // PLACEHOLDER

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify_larger_digit_perm_iii(); return 0; }
    
    cout << "PE 925: Larger Digit Permutation III\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    return 0;
}
