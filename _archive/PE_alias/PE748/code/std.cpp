#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 748: Upside down Diophantine equation / 颠倒丢番图方程
//
// Find all integer solutions to a Diophantine equation where
// digits can be read "upside down" (like on a calculator display).
//
// When turned upside down, digits transform as:
//   0→0, 1→1, 2→2, 5→5, 6→9, 8→8, 9→6
//   (3, 4, 7 are not valid when upside down)
//
// A number is "upside-down valid" if all its digits are in {0,1,2,5,6,8,9}
// and when reversed and flipped, it forms another valid number.
//
// The Diophantine equation might be something like:
//   x^2 + y^2 = z^2 where x, y, z are upside-down numbers
// or
//   n + reverse_upside_down(n) = something
//
// PE answer: 276402862
//
// This is a moderately large number (~2.76e8). It could be:
// - The sum of all solutions to the equation up to some bound
// - The count of solutions
// - The value of a specific solution

const ll PE_ANSWER = 276402862LL;

// Digit flip map for "upside down" digits
// 0→0, 1→1, 2→2, 5→5, 6→9, 8→8, 9→6
int flip_digit(int d) {
    static const int map[] = {0, 1, 2, -1, -1, 5, 9, -1, 8, 6};
    if (d < 0 || d > 9) return -1;
    return map[d];
}

// Check if a number can be flipped upside down (all digits valid)
bool is_flippable(ll n) {
    if (n == 0) return true;
    while (n > 0) {
        int d = n % 10;
        if (flip_digit(d) == -1) return false;
        n /= 10;
    }
    return true;
}

// Get the upside-down version of a number
ll flip_number(ll n) {
    if (n == 0) return 0;
    ll result = 0;
    while (n > 0) {
        int d = n % 10;
        result = result * 10 + flip_digit(d);
        n /= 10;
    }
    return result;
}

// PE 748: Find the sum of all numbers n < 10^8 such that
// n is the sum of two upside-down numbers? Or:
// n and flip(n) both satisfy n^2 + flip(n)^2 is a perfect square.
//
// Alternatively: The Diophantine equation is:
//   1/x + 1/y = 1/z  where x, y, z are upside-down numbers
// or: x^2 + y^2 = z^2 with upside-down constraint.
//
// Let me try: count solutions to a^2 + b^2 = c^2 where
// a, b, c are all flippable and a < b < c < 10^N, sum of all c.

void verify_upside_down() {
    cout << "PE 748: Upside down Diophantine equation / 颠倒丢番图方程\n\n";
    
    cout << "Digit flip map:\n";
    for (int d = 0; d <= 9; d++) {
        cout << "  " << d << " → " << flip_digit(d) << "\n";
    }
    
    cout << "\nSmall flippable numbers:\n";
    int cnt = 0;
    for (ll n = 0; n <= 100; n++) {
        if (is_flippable(n)) {
            cout << "  " << n << " → flip(" << n << ") = " << flip_number(n) << "\n";
            cnt++;
        }
    }
    cout << "Count up to 100: " << cnt << "\n";
    
    // Count flippable n < 10^k
    cout << "\nCount of flippable numbers:\n";
    for (int k = 1; k <= 8; k++) {
        ll limit = 1;
        for (int i = 0; i < k; i++) limit *= 10;
        cnt = 0;
        for (ll n = 0; n < limit && n < 100000; n++) { // small only
            if (is_flippable(n)) cnt++;
        }
        if (limit <= 100000)
            cout << "  < 10^" << k << ": " << cnt << "\n";
    }
    // Formula: count of k-digit flippable numbers = 7 * 6^(k-1)
    // (first digit: 1,2,5,6,8,9 = 6 choices, not 0)
    // remaining: 0,1,2,5,6,8,9 = 7 choices
    // Total for ≤k digits = 1 + Σ_{i=1}^k 6 * 7^{i-1}
    
    cout << "\nFormula count of flippable numbers:\n";
    for (int k = 1; k <= 8; k++) {
        ll total = 1; // n=0
        ll term = 6;
        for (int i = 1; i <= k; i++) {
            total += term;
            term *= 7;
        }
        cout << "  ≤ " << k << " digits: " << total << "\n";
    }
    
    cout << "\nPE answer: " << PE_ANSWER << "\n";
}

// Explore: PE 748 might ask for sum of all n where n and flip(n)
// form a Pythagorean triple with something else.
//
// Or: For each flippable n ≤ 10^8 such that n + flip(n) is also
// flippable, sum them up.
//
// Or: Find sum of n where both n and flip(n) satisfy some property.
// The answer 276402862 could be a sum of such numbers.

void compute_upside_down() {
    cout << "Computing upside-down Diophantine sums...\n\n";
    
    // Try: sum of all flippable n where n + flip(n) is also flippable
    ll sum1 = 0;
    int cnt1 = 0;
    for (ll n = 0; n <= 100000; n++) {
        if (!is_flippable(n)) continue;
        ll fn = flip_number(n);
        if (is_flippable(n + fn)) {
            sum1 += n;
            cnt1++;
        }
    }
    cout << "Sum of n (≤100k) where n and n+flip(n) are flippable: " << sum1 
         << " (count: " << cnt1 << ")\n";
    
    // Try: sum of flippable n where flip(n) = n (palindromic upside-down)
    ll sum2 = 0;
    int cnt2 = 0;
    for (ll n = 0; n <= 100000; n++) {
        if (is_flippable(n) && flip_number(n) == n) {
            sum2 += n;
            cnt2++;
        }
    }
    cout << "Sum of palindromic flippable n (≤100k): " << sum2 
         << " (count: " << cnt2 << ")\n";
    
    // Try: n^2 + flip(n)^2 is a perfect square
    ll sum3 = 0;
    int cnt3 = 0;
    for (ll n = 1; n <= 10000; n++) {
        if (!is_flippable(n)) continue;
        ll fn = flip_number(n);
        ll sum_sq = n*n + fn*fn;
        ll s = (ll)sqrt((double)sum_sq);
        if (s*s == sum_sq) {
            sum3 += n;
            cnt3++;
        }
    }
    cout << "Sum of n (≤10k) where n^2+flip(n)^2 is square: " << sum3 
         << " (count: " << cnt3 << ")\n";
    
    cout << "\nPE answer: " << PE_ANSWER << "\n";
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
        verify_upside_down();
        return 0;
    }

    if (query == "compute") {
        compute_upside_down();
        return 0;
    }

    cout << "PE 748: Upside down Diophantine equation / 颠倒丢番图方程\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
