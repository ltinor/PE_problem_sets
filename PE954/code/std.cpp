#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 954: Heptaphobia / 恐七数
//
// A positive integer is "heptaphobic" if:
//   - It is NOT divisible by 7.
//   - No number divisible by 7 can be produced by swapping any two of its digits.
// Leading zeros are not allowed before or after the swap.
//
// Examples: 17 and 1305 are heptaphobic.
// 14 is not (divisible by 7). 132 is not (swap 1<->2 → 231 = 7×33).
//
// C(N) = count of heptaphobic numbers < N.
// Given: C(100) = 74, C(10^4) = 3737.
// Find C(10^13).
//
// Key observations:
// - A number is heptaphobic iff it's not divisible by 7 AND no digit swap
//   creates a multiple of 7.
//
// - Let's analyze the condition for a d-digit number.
// - For a number with digits a_1 a_2 ... a_d (most significant first),
//   its value mod 7 is: Σ a_i · 10^{d-i} (mod 7).
// - Swapping positions i and j changes the value mod 7 by:
//   Δ = (a_j - a_i)·10^{d-i} + (a_i - a_j)·10^{d-j}
//     = (a_j - a_i)·(10^{d-i} - 10^{d-j}) (mod 7).
//
// - So a swap creates a multiple of 7 iff:
//   V + Δ ≡ 0 (mod 7), where V is the original value mod 7.
//   Equivalent to: Δ ≡ -V (mod 7).
//
// - For a number to be heptaphobic:
//   1. V ≠ 0 (mod 7)  — not divisible by 7.
//   2. For all pairs (i,j) with i≠j: V + Δ_{ij} ≠ 0 (mod 7),
//      i.e., Δ_{ij} ≠ -V (mod 7).
//
// - Note: 10^k mod 7 cycles with period 6: 1,3,2,6,4,5,1,3,2,...
//   So 10^{d-i} mod 7 depends only on (d-i) mod 6.
//
// - For each position i, let w_i = 10^{d-i} mod 7.
//   Δ_{ij} = (a_j - a_i)·(w_i - w_j) mod 7.
//
// - This can be precomputed for each pair of positions.
//
// - Since d ≤ 13 for N = 10^13, we can do DP over digits.
//   State: (position, value_mod_7, set of possible swap deltas?) 
//
// - Actually, the condition can be simplified. For a given multiset of
//   digits and their positions, we can check all O(d²) swaps.
//
// - Approach: digit DP with state tracking the multiset of digits
//   in each "weight class" (positions with same 10^k mod 7).
//
// - The weights mod 7 for positions (from rightmost, 0-indexed):
//   pos 0: 1, pos 1: 3, pos 2: 2, pos 3: 6, pos 4: 4, pos 5: 5, pos 6: 1, ...
//
// - There are only 6 weight classes (mod 7 cycle of length 6).
//   For d digits, we know exactly how many positions are in each class.
//
// - Let cnt[w] = number of positions with weight w (w ∈ {1,3,2,6,4,5}).
//   Total value mod 7 = Σ_{w} w·(sum of digits in weight-w positions) mod 7.
//
// - For a swap between a digit at position with weight w_i and a digit
//   at position with weight w_j, the change is:
//   Δ = (a_j - a_i)·(w_i - w_j) mod 7.
//   Since w_i, w_j are from {1,3,2,6,4,5}, the possible values of (w_i - w_j)
//   mod 7 can be precomputed.
//
// - The condition that NO swap produces 0 mod 7 means:
//   For every pair of positions (i,j) with digits a_i, a_j:
//     V + (a_j - a_i)·(w_i - w_j) ≠ 0 (mod 7).
//
// - Since the number of possible values of (w_i - w_j) mod 7 is limited
//   (at most 6 values for each pair of weight classes), we can represent
//   forbidden digit differences for each weight class pair.
//
// - This is a combinatorial enumeration over digit multisets per weight class.
// - Let's do DP to count valid d-digit numbers for d = 1..13.
//
// - For each d, compute number of heptaphobic numbers with exactly d digits.
//   Then C(10^13) = Σ_{d=1}^{13} count_d (since 10^13 has 14 digits, we want < 10^13).
//
// - Actually C(N) counts numbers < N, so for N = 10^13, it's all numbers
//   with at most 13 digits, or the 13-digit numbers less than N (= all of them
//   since N = 10^13 is exactly the first 14-digit number).
//   So C(10^13) = sum of heptaphobic numbers with 1 to 13 digits.
//
// - PE answer: (to be computed)

const ll PE_ANSWER = 0; // placeholder

// Precompute 10^k mod 7
const int POW10_MOD7[6] = {1, 3, 2, 6, 4, 5};

// Weight differences mod 7
int weight_diff[6][6];

void init_weight_diff() {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            weight_diff[i][j] = (POW10_MOD7[i] - POW10_MOD7[j] + 7) % 7;
}

// Count heptaphobic numbers for a fixed number of digits d
ll count_heptaphobic_d(int d) {
    if (d == 0) return 0;
    
    // For d-digit numbers: positions 0..d-1 (0 = most significant)
    // Weight at position p: 10^{d-1-p} mod 7
    // Equivalent to position from rightmost: w = 10^{(d-1-p)} mod 7
    // = POW10_MOD7[(d-1-p) % 6]
    
    // Count positions per weight class
    vector<int> pos_cnt(6, 0);
    for (int p = 0; p < d; p++) {
        int w_idx = (d - 1 - p) % 6;
        pos_cnt[w_idx]++;
    }
    
    // DP: iterate over positions from most significant to least.
    // State: (pos, mod7_value, digit_assignments per weight class)
    // This is too large for d=13 with 10 digits.
    
    // Alternative: enumerate digit distribution and check.
    // For d up to 13, total combinations = 10^13 = 10 trillion, too many.
    
    // Better: use inclusion-exclusion or combinatorial counting.
    // The condition only depends on differences between digits in
    // different weight classes.
    
    // For a given weight class, all positions have the same weight w.
    // Swapping two digits within the same weight class gives Δ = 0
    // (since w_i = w_j), so this never creates a multiple of 7.
    // So we only need to worry about swaps between different weight classes.
    
    // For each pair of weight classes (w_i, w_j), the swap condition is:
    //   V + (a_j - a_i)·(w_i - w_j) ≠ 0 (mod 7)
    // For each digit in class i and each digit in class j.
    
    // This is a constraint on digit multisets per class.
    // Since there are at most 6 weight classes, each with ≤ ceil(d/6) positions,
    // we can use DP over weight classes.
    
    // Actually, let me use a meet-in-the-middle or direct enumeration
    // for the weight class approach.
    
    return 0; // placeholder
}

// Brute force check for a single number
bool is_heptaphobic(ll n) {
    if (n % 7 == 0) return false;
    
    string s = to_string(n);
    int d = s.size();
    ll orig_mod7 = n % 7;
    
    for (int i = 0; i < d; i++) {
        for (int j = i + 1; j < d; j++) {
            if (s[i] == s[j]) continue; // swap doesn't change number
            
            // Don't allow leading zero after swap
            if (i == 0 && s[j] == '0') continue;
            if (j == 0 && s[i] == '0') continue;
            
            // Compute new value mod 7
            // Δ = (a_j - a_i)·10^{d-1-i} + (a_i - a_j)·10^{d-1-j}
            ll w_i = 1, w_j = 1;
            for (int k = 0; k < d - 1 - i; k++) w_i = (w_i * 10) % 7;
            for (int k = 0; k < d - 1 - j; k++) w_j = (w_j * 10) % 7;
            
            int ai = s[i] - '0', aj = s[j] - '0';
            ll delta = ((aj - ai) * w_i + (ai - aj) * w_j) % 7;
            delta = (delta + 7) % 7;
            
            if ((orig_mod7 + delta) % 7 == 0) return false;
        }
    }
    return true;
}

void verify() {
    cout << "PE 954: Heptaphobia / 恐七数\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "Heptaphobic numbers: not divisible by 7, and no digit swap\n";
    cout << "creates a multiple of 7 (no leading zeros).\n";
    cout << "C(N) = count of heptaphobic numbers < N.\n";
    cout << "C(100) = 74, C(10^4) = 3737. Find C(10^13).\n\n";
    
    cout << "=== Verification (small values) ===\n";
    // Verify C(100)
    ll C100 = 0;
    for (ll n = 1; n < 100; n++) {
        if (is_heptaphobic(n)) C100++;
    }
    cout << "C(100) = " << C100 << " (expected 74)\n";
    
    // Examples
    cout << "is_heptaphobic(17) = " << is_heptaphobic(17) << " (expected 1)\n";
    cout << "is_heptaphobic(14) = " << is_heptaphobic(14) << " (expected 0)\n";
    cout << "is_heptaphobic(132) = " << is_heptaphobic(132) << " (expected 0)\n";
    cout << "is_heptaphobic(1305) = " << is_heptaphobic(1305) << " (expected 1)\n\n";
    
    cout << "=== Analysis ===\n";
    cout << "For d-digit numbers, weights = 10^{d-1-pos} mod 7.\n";
    cout << "10^k mod 7 cycle: [1,3,2,6,4,5] with period 6.\n";
    cout << "Only 6 weight classes; swaps within same class don't matter.\n";
    cout << "Constraint: for each (class_i, class_j): (a_j - a_i)*(w_i - w_j) ≠ -V.\n\n";
    
    cout << "=== Target ===\n";
    cout << "C(10^13) = sum of heptaphobic numbers with 1-13 digits.\n";
    cout << "Can use DP over weight classes with digit distribution.\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    init_weight_diff();
    
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 954: Heptaphobia / 恐七数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
