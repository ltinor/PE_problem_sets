#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 206: Concealed Square
// Input: pattern string (e.g., "1_2_3_4_5_6_7_8_9_0")
// Output: smallest n such that n^2 matches the pattern
// PE Answer (pattern "1_2_3_4_5_6_7_8_9_0"): 1389019170

bool matches(const string& s, const string& pattern) {
    int len = s.size();
    if (len != (int)pattern.size()) return false;
    for (int i = 0; i < len; i++) {
        if (pattern[i] == '_') continue;
        if (s[i] != pattern[i]) return false;
    }
    return true;
}

string to_string_i128(__int128 x) {
    if (x == 0) return "0";
    string s;
    while (x) { s += char('0' + (int)(x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string pattern;
    cin >> pattern;

    int L = pattern.size();
    // n^2 has L digits
    // n is about sqrt(10^(L-1)) to sqrt(10^L - 1)
    ll lo = (ll)ceil(sqrt(pow(10, L - 1) - 0.5));
    ll hi = (ll)floor(sqrt(pow(10, L) - 1.5));

    // If pattern ends with '0', n must end with 0
    // More generally: check if last digit of pattern constrains n mod 10
    int step = 1;
    if (pattern.back() == '0') step = 10;
    else {
        // Check which last digits of n^2 can match pattern's last char
        int last_digit = pattern.back() - '0';
        bool found = false;
        for (int d = 0; d <= 9; d++) {
            if ((d * d) % 10 == last_digit) {
                if (!found) { lo = ((lo + d) / 10) * 10 + d; found = true; }
            }
        }
        // Just step by 10 through possible endings
        if (!found) step = 1;
    }

    // Align lo to first valid candidate
    if (step > 1) {
        ll mod = lo % step;
        ll target_mod = 0; // n^2 ending in pattern's last digit
        if (pattern.back() == '0') target_mod = 0;
        else if (pattern.back() == '1') target_mod = 1;
        else if (pattern.back() == '4') target_mod = 2;
        else if (pattern.back() == '5') target_mod = 5;
        else if (pattern.back() == '6') target_mod = 6;
        else if (pattern.back() == '9') target_mod = 3;
        else {
            // For other digits, step by 1
            step = 1;
        }
        if (step > 1) {
            lo = ((lo - target_mod + step) / step) * step + target_mod;
            if (lo * lo < (ll)pow(10, L - 1)) lo += step;
        }
    }

    // Actually, simpler approach: since we stepped by 10 when last is 0,
    // and for general pattern, just brute force step 1 with early exit
    // For performance on large patterns, use step = 10 when last digit is 0 or 5
    
    step = 1;
    if (pattern.back() == '0') {
        step = 10;
        while (lo % 10 != 0) lo++;
    }

    for (ll n = lo; n <= hi; n += step) {
        __int128 sq = (__int128)n * n;
        string sq_str = to_string_i128(sq);
        if (matches(sq_str, pattern)) {
            cout << n << "\n";
            return 0;
        }
    }

    // Should not reach here for valid patterns
    cout << "0\n";
    return 0;
}
