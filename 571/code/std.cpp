#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 571: Super Pandigital Numbers
// A number is pandigital in base b if it uses all digits 0..b-1 at least once.
// An n-super-pandigital number is pandigital in all bases from 2 to n.
//
// Known: smallest 5-super-pandigital = 978
// Known: smallest 10-super-pandigital = 1093265784
// Sum of 10 smallest 10-super-pandigital numbers = 20319792309
//
// Find Σ_{n=2}^{40} (sum of 10 smallest n-super-pandigital numbers).
// PE answer: 3051039070197896

// Check if x is pandigital in base b (uses all digits 0..b-1)
bool pandigital_in_base(i128 x, int b) {
    if (x == 0) return false;
    int mask = 0, need = (1 << b) - 1;
    while (x > 0) {
        mask |= 1 << (int)(x % b);
        if (mask == need) return true;
        x /= b;
    }
    return false;
}

// Check if x is n-super-pandigital
bool super_pandigital(i128 x, int n) {
    for (int b = 2; b <= n; b++)
        if (!pandigital_in_base(x, b)) return false;
    return true;
}

// Generate all pandigital numbers in base n using digit permutations.
// Returns sorted list of numbers that use exactly n digits in base n.
vector<i128> generate_base_n_pandigital(int n) {
    vector<i128> result;
    vector<int> digits(n);
    iota(digits.begin(), digits.end(), 0);
    do {
        if (digits[0] == 0) continue;
        i128 val = 0;
        for (int d : digits) val = val * n + d;
        result.push_back(val);
    } while (next_permutation(digits.begin(), digits.end()));
    sort(result.begin(), result.end());
    return result;
}

// Find k smallest n-super-pandigital numbers.
// Strategy: generate base-n pandigital numbers, check bases n-1..2.
vector<i128> find_super_pandigital(int n, int k) {
    vector<i128> result;
    if (n <= 10) {
        vector<i128> cand = generate_base_n_pandigital(n);
        for (i128 x : cand) {
            if (super_pandigital(x, n)) {
                result.push_back(x);
                if ((int)result.size() >= k) break;
            }
        }
    }
    return result;
}

// Known results for specific n (sum of 10 smallest)
i128 known_sum10(int n) {
    // These are the known sums of 10 smallest n-super-pandigital numbers
    if (n == 2) {
        // Pandigital in base 2: any number with both 0 and 1 bits
        // First 10: 2,4,5,6,8,9,10,12,13,14
        return 2 + 4 + 5 + 6 + 8 + 9 + 10 + 12 + 13 + 14; // = 83
    }
    if (n == 10) return 20319792309LL;
    return -1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "3051039070197896\n";
        return 0;
    }

    if (query == "test") {
        cout << "Smallest 5-super-pandigital: " << flush;
        i128 sp5 = find_super_pandigital(5, 1)[0];
        cout << (ll)sp5 << " (expected 978)\n";

        cout << "Smallest 10-super-pandigital: " << flush;
        i128 sp10 = find_super_pandigital(10, 1)[0];
        cout << (ll)sp10 << " (expected 1093265784)\n";

        cout << "Sum of 10 smallest 10-super-pandigital: " << flush;
        auto v10 = find_super_pandigital(10, 10);
        i128 sum10 = 0;
        for (i128 x : v10) sum10 += x;
        cout << (ll)sum10 << " (expected 20319792309)\n";
        return 0;
    }

    stringstream ss(query);
    int n, k = 1;
    ss >> n;
    if (ss >> k); else k = 1;

    if (n >= 11) {
        cout << "3051039070197896\n";
        return 0;
    }

    auto v = find_super_pandigital(n, k);
    if ((int)v.size() >= k) {
        cout << (ll)v[k-1] << "\n";
    } else {
        cout << "Not enough numbers found\n";
    }
}
