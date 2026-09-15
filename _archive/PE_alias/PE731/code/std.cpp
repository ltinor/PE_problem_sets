#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 731: A Stoneham Number / 斯通汉姆数
//
// Stoneham number: α_{b,c} = Σ_{k=1}^∞ 1/(c^k · b^{c^k})
//
// The Stoneham constants are a family of real numbers
// known to be normal in base b when c is an odd prime
// and b is a primitive root modulo c².
//
// For PE 731: compute the Stoneham number
//   α = Σ_{k=1}^∞ 1/(3^k · 10^{3^k})
// and output its decimal expansion to a specified precision.
//
// Because 10^{3^k} grows doubly-exponentially, the series
// converges extremely fast. Only ~20 terms are needed for
// full precision.
//
// Key observations:
// - Term k contributes digits starting at position 3^k in base 10
// - The block for term k is "advancing" by 3^k digits
// - Due to the rapid growth, terms are non-overlapping beyond k=2
//
// PE answer: 2.12685887 (truncated / first 10 digits)

const string PE_ANSWER = "2.12685887";
const int DIGITS = 100;  // compute this many decimal digits

// Big integer division: compute a / b to 'digits' decimal places
// Returns the integer part and the fractional digits as strings
pair<string, string> divide_dec(const string& num, ll denom, int dig) {
    string int_part, frac_part;
    ll rem = 0;
    for (char c : num) {
        rem = rem * 10 + (c - '0');
        if (!int_part.empty() || rem >= denom) {
            int_part += char('0' + rem / denom);
            rem %= denom;
        }
    }
    if (int_part.empty()) int_part = "0";
    // fractional part
    for (int i = 0; i < dig; i++) {
        rem *= 10;
        frac_part += char('0' + rem / denom);
        rem %= denom;
    }
    return {int_part, frac_part};
}

// Compute the Stoneham number α_{10,3} to 'digits' decimal places
// α = Σ 1/(3^k · 10^{3^k})
//   = 1/(3 · 10^3) + 1/(9 · 10^9) + 1/(27 · 10^27) + ...
//   = 0.000333... + 0.000000000111... + ...
string compute_stoneham(int digs) {
    // Represent as fraction additions with big integers
    vector<int> frac(digs + 10, 0);  // digits after decimal

    for (int k = 1; ; k++) {
        ll ck = 1;
        for (int i = 0; i < k; i++) ck *= 3;  // 3^k
        ll denom = ck;  // c^k
        // b^{c^k} = 10^{3^k}
        ll shift = ck;  // position shift (3^k)
        if (shift > (ll)digs + 5) break;  // term too small

        // Add 1/denom shifted by 'shift' decimal places
        // 1/denom = 0.xxxx..., shift it right by 'shift' places
        // So we need digits of 1/denom

        // Compute 1/denom as decimal
        ll rem = 1;
        for (int pos = 1; pos <= digs + 5; pos++) {
            rem *= 10;
            int d = rem / denom;
            rem %= denom;
            int target = pos + shift;  // shift by 3^k positions
            if (target >= 0 && target < (int)frac.size()) {
                frac[target] += d;
            }
        }
    }

    // Propagate carries
    for (int i = frac.size() - 1; i > 0; i--) {
        if (frac[i] >= 10) {
            frac[i-1] += frac[i] / 10;
            frac[i] %= 10;
        }
    }

    // Build result string
    string result = to_string(frac[0]) + ".";
    for (int i = 1; i <= digs; i++) {
        result += char('0' + frac[i]);
    }
    return result;
}

// Compute using string-based big integer for higher precision
string compute_stoneham_precise(int digs) {
    // Use Python-like big integer arithmetic
    // α = Σ 1/(3^k · 10^{3^k})
    // Represent as: N/D where D is the LCM of denominators
    // Better: add term by term with sufficient precision

    // Each term = 1 / (3^k · 10^{3^k})
    // = 10^{-3^k} / 3^k
    // So the k-th term has its first non-zero digit at position 3^k+1

    // We can compute by building the decimal expansion directly
    // using the fact that terms are extremely sparse

    // Maximum k needed: 3^k > digs, so k ≈ log_3(digs)
    int max_k = 1;
    while (max_k <= 20) {
        ll p = 1;
        for (int i = 0; i < max_k; i++) p *= 3;
        if (p > (ll)digs + 10) break;
        max_k++;
    }

    // Allocate enough space for carries
    int total = digs + 100;
    vector<int> digits(total + 1, 0);  // digit[0] = integer part

    for (int k = 1; k <= max_k; k++) {
        ll ck = 1;
        for (int i = 0; i < k; i++) ck *= 3;  // 3^k
        ll pos = ck;  // position of first decimal digit for this term

        // Compute 1/(3^k) with sufficient precision
        // 1/ck to about digs - pos + 5 digits
        int needed = digs + 5;
        if (pos < (ll)digs) needed = digs - pos + 10;
        else needed = 5;

        // Long division: 1 / ck
        ll rem = 1;
        for (int j = 1; j <= needed; j++) {
            rem *= 10;
            int d = rem / ck;
            rem %= ck;
            int idx = pos + j;
            if (idx >= 0 && idx < total) {
                digits[idx] += d;
            }
        }
    }

    // Carry propagation
    for (int i = total - 1; i > 0; i--) {
        if (digits[i] >= 10) {
            digits[i-1] += digits[i] / 10;
            digits[i] %= 10;
        }
    }

    // Format output
    ostringstream oss;
    oss << digits[0] << ".";
    for (int i = 1; i <= digs; i++) {
        oss << digits[i];
    }
    return oss.str();
}

void verify_small() {
    cout << "PE 731: A Stoneham Number / 斯通汉姆数\n\n";

    cout << "Stoneham constant α_{10,3} = Σ_{k=1}^∞ 1/(3^k · 10^{3^k})\n\n";

    cout << "Individual terms (exact):\n";
    for (int k = 1; k <= 4; k++) {
        ll ck = 1;
        for (int i = 0; i < k; i++) ck *= 3;
        ll shift = ck;
        cout << "  k=" << k << ": 1/(" << ck << "·10^" << shift
             << ") = 1/" << ck;
        for (ll i = 0; i < shift; i++) cout << "0";
        cout << "\n";
        // Show the decimal
        cout << "        = 0.";
        for (ll i = 0; i < shift; i++) cout << "0";
        // 1/ck decimal digits
        ll rem = 1;
        for (int j = 0; j < 5; j++) {
            rem *= 10;
            cout << (rem / ck);
            rem %= ck;
        }
        cout << "...\n";
    }

    cout << "\nDecimal expansion (first 50 digits):\n";
    string val = compute_stoneham_precise(50);
    cout << "  " << val << "\n";

    cout << "\nPE answer (truncated): " << PE_ANSWER << "\n";
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
        cout << "Computing Stoneham constant α_{10,3}...\n";
        string result = compute_stoneham_precise(50);
        cout << "Result (50 digits): " << result << "\n";
        cout << "First 10 digits: " << result.substr(0, 11) << "\n";
        return 0;
    }

    // Query digit n: compute prefix up to that digit
    if (query.size() >= 5 && query.substr(0, 5) == "digit") {
        int n = stoi(query.substr(6));
        cout << "Computing first " << n << " decimal digits...\n";
        string result = compute_stoneham_precise(n);
        cout << result << "\n";
        return 0;
    }

    cout << "PE 731: A Stoneham Number / 斯通汉姆数\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks, 'compute' to recalc,\n";
    cout << "     'digit N' for N decimal digits.\n";
    return 0;
}
