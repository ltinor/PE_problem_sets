#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 961: Removing Digits / 删除数字
//
// Two players take turns removing one digit from a positive integer.
// After removal, leading zeros are also removed.
// Winner: the player who removes the last non-zero digit.
//
// W(N) = count of positive integers < N where first player can force a win.
// Given: W(100) = 18, W(10^4) = 1656.
// Find W(10^18).
//
// Key observations:
// - This is an impartial combinatorial game on the digits of a number.
// - The game state is a multiset of digits (with leading zeros removed).
// - Removing a digit effectively reduces the number.
//
// - After removing a digit and stripping leading zeros, the number
//   either becomes a shorter positive integer or 0.
//
// - The game ends when only zeros remain (or the number becomes 0).
//   The player who removes the LAST non-zero digit wins.
//
// - This means: the game is about reducing the number to 0.
//   A player who makes the number 0 wins (since they removed the last
//   non-zero digit).
//
// - Wait: "the winner is the person who removes the last nonzero digit."
//   If I remove the last non-zero digit, the number becomes 0 (after
//   stripping zeros). Then the next player faces 0 and can't move,
//   so they lose. So yes, the player who makes the number 0 wins.
//
// - So this is a normal-play impartial game where the terminal position
//   is 0 (no digits left).
//
// - The moves from a number N: remove any one digit from its decimal
//   representation, then strip leading zeros.
//
// - For a number with d digits: there are d possible moves (remove each
//   digit position). But some moves may lead to the same result
//   (e.g., if there are duplicate digits or zeros at the front).
//
// - The Grundy value (nimber) of a position determines winning/losing.
//   A position is losing (P-position) for the first player iff Grundy = 0.
//
// - The Grundy value depends on the multiset of digits and their positions.
//   However, after stripping leading zeros, the result is just a number
//   with no leading zeros.
//
// - We need to count numbers < 10^18 where the first player has a winning
//   strategy (Grundy ≠ 0).
//
// - Since the game treats numbers as the game states, and the moves
//   depend on the digit representation, we can compute Grundy values
//   via DP for all numbers up to some limit, then look for patterns.
//
// - d ≤ 18 for N = 10^18 (numbers with at most 18 digits, since < 10^18
//   means at most 18-digit numbers less than 10^18).
//
// - Key simplification: since leading zeros are stripped, numbers are
//   represented without leading zeros. So a number with k digits has
//   most significant digit in {1..9} and other digits in {0..9}.
//
// - The game is finite (each move reduces the number of non-zero digits
//   or the total digit count). The maximum depth is the number of
//   non-zero digits.
//
// - For each number, the Grundy value g(n) depends on g(n') for all
//   possible moves n → n'.
//
// - Since there are 9 × 10^{d-1} d-digit numbers, for d=18 that's
//   about 9 × 10^{17} — far too many to enumerate.
//
// - Need a combinatorial characterization. The game is essentially
//   about the multiset of non-zero digits.
//
// - Let's analyze small positions:
//   - Numbers 1-9: one digit. Removing it gives 0 (terminal, losing).
//     So g(1)=g(2)=...=g(9) = mex({g(0)}) = mex({0}) = 1. All winning.
//   - Numbers 10-99: two digits.
//     Let's compute systematically.
//
// - Is the Grundy value determined solely by the multiset of non-zero
//   digits and the count of zeros? Or does digit position matter?
//
// - Example: 105. Digits: 1,0,5.
//   Remove 1 → 05 = 5. Remove 0 → 15. Remove 5 → 10.
//   The result depends on which digit we remove and position.
//
// - Position matters! 150 vs 105 have the same digits but different results.
//   Remove 1 from 150 → 50. Remove 5 from 150 → 10.
//   Remove 1 from 105 → 5. Remove 5 from 105 → 10.
//
// - So the game state is the actual number, not just digit multiset.
//
// - But perhaps the Grundy value depends only on the "pattern" of digits
//   relative to the most significant position?
//
// - Let's think about the problem differently. Since d ≤ 18, maybe we
//   can do DP by enumerating all possible digit patterns more efficiently.
//
// - Actually, 10^18 is the total count. Most (9/10) of numbers < 10^18
//   have exactly 18 digits. So total count ≈ 10^18, which is too large.
//
// - Need a mathematical characterization. Let me look at the Grundy
//   values for small numbers and see if there's a pattern.
//
// - PE answer: (to be computed)

const ll PE_ANSWER = 0; // placeholder

// Compute Grundy values for small numbers via DP
map<ll, int> grundy_cache;

int grundy(ll n) {
    if (n == 0) return 0; // terminal
    if (grundy_cache.count(n)) return grundy_cache[n];
    
    string s = to_string(n);
    set<int> reachable;
    
    for (int i = 0; i < (int)s.size(); i++) {
        string t = s.substr(0, i) + s.substr(i + 1);
        // Strip leading zeros
        while (t.size() > 1 && t[0] == '0') t = t.substr(1);
        ll m = t.empty() ? 0 : stoll(t);
        reachable.insert(grundy(m));
    }
    
    int g = 0;
    while (reachable.count(g)) g++;
    return grundy_cache[n] = g;
}

void verify() {
    cout << "PE 961: Removing Digits / 删除数字\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "Two players take turns removing one digit. Leading zeros stripped.\n";
    cout << "Winner removes last non-zero digit (makes number 0).\n";
    cout << "W(N) = count of n < N where first player wins.\n";
    cout << "W(100)=18, W(10^4)=1656. Find W(10^18).\n\n";
    
    cout << "=== Verification ===\n";
    ll W100 = 0;
    for (ll n = 1; n < 100; n++) {
        if (grundy(n) != 0) W100++;
    }
    cout << "W(100) = " << W100 << " (expected 18)\n";
    
    // W(10^4) would be slower but let's try
    ll W10k = 0;
    for (ll n = 1; n < 10000; n++) {
        if (grundy(n) != 0) W10k++;
    }
    cout << "W(10^4) = " << W10k << " (expected 1656)\n\n";
    
    cout << "=== Pattern Analysis ===\n";
    cout << "Grundy values for 1-digit numbers:\n";
    for (ll n = 1; n <= 9; n++) {
        cout << "  g(" << n << ") = " << grundy(n) << "\n";
    }
    cout << "\nTwo-digit examples:\n";
    for (ll n = 10; n <= 19; n++) {
        cout << "  g(" << n << ") = " << grundy(n) << "\n";
    }
    cout << "\n";
    
    cout << "=== Target ===\n";
    cout << "W(10^18): need to characterize winning positions among\n";
    cout << "all numbers with ≤18 digits (no leading zeros).\n";
    cout << "Grundy values likely depend on digit pattern.\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 961: Removing Digits / 删除数字\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
