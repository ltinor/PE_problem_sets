#include<bits/stdc++.h>
using namespace std;
using i128 = __int128;

// First 15 primes
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
const int NP = 15;

i128 best_n;
i128 target; // 2*K + 1 (need prod(2e+1) > target-1 → prod >= target)

// Print __int128
void print_i128(i128 x) {
    if (x == 0) { cout << "0"; return; }
    if (x < 0) { cout << "-"; x = -x; }
    string s;
    while (x > 0) { s += char('0' + (x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

// Quick pow for i128
i128 ipow(i128 a, int e) {
    i128 r = 1;
    while (e) {
        if (e & 1) r *= a;
        a *= a;
        e >>= 1;
    }
    return r;
}

// max exponent for prime p such that p^e doesn't overflow best_n
int max_exp(int p, i128 limit) {
    int e = 0;
    i128 cur = 1;
    while (cur <= limit / p) {
        cur *= p;
        e++;
    }
    return e;
}

// DFS: idx = prime index, prev_e = max exponent from previous level
// cur_n = current n, cur_div = prod(2e_i + 1) so far
void dfs(int idx, int prev_e, i128 cur_n, i128 cur_div) {
    if (cur_div >= target) {
        if (cur_n < best_n) best_n = cur_n;
        return;
    }
    if (idx >= NP) return;

    int p = primes[idx];
    // Maximum exponent we can try: bounded by prev_e and by overflow
    int max_e = min(prev_e, max_exp(p, best_n / cur_n));

    i128 p_pow = 1; // p^e
    for (int e = 0; e <= max_e; e++) {
        i128 new_n = cur_n * p_pow;
        if (new_n >= best_n) break;

        i128 new_div = cur_div * (2 * e + 1);

        // Pruning: even if all remaining primes contribute factor 3 each
        // (which is the minimum when e_i = 1), can we reach target?
        // Max possible remaining factor = 3^(NP - idx - 1)
        i128 max_possible = new_div;
        for (int r = idx + 1; r < NP && max_possible < target; r++) {
            max_possible *= 3;
        }

        if (max_possible >= target) {
            dfs(idx + 1, e, new_n, new_div);
        }

        // Prepare for next exponent
        if (e < max_e) {
            // Check overflow before multiplying
            if (p_pow > best_n / p) break;
            p_pow *= p;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i128 K;
    long long K_in;
    cin >> K_in;
    K = K_in;

    target = 2 * K + 1; // need prod(2e_i+1) >= 2K+1 (strictly > 2K)
    best_n = (i128)1 << 62; // a very large number as initial bound

    // Start DFS from prime index 0, with effectively unlimited prev_e
    dfs(0, 60, 1, 1);

    print_i128(best_n);
    cout << "\n";
    return 0;
}
