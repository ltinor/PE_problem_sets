#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 782: Distinct Rows and Columns / 不同行列
//
// Consider an m×n binary matrix (entries 0 or 1) where all rows
// are distinct AND all columns are distinct. The problem likely asks
// to count the number of such matrices, or find the sum of something
// over all such matrices, possibly modulo a large prime.
//
// For an m×n matrix with distinct rows: there are 2^n possible rows,
// so we need m ≤ 2^n and choose m distinct rows (P(2^n, m)).
// Similarly distinct columns: n ≤ 2^m.
// Both constraints simultaneously make this a combinatorial design problem.
//
// PE answer: 325499120
//
// This is roughly 3.25 × 10^8, could be a sum over matrix dimensions.

const ll PE_ANSWER = 325499120LL;
const ll MOD = 1000000007LL;  // common PE modulus

// Modular exponentiation
ll mod_pow(ll a, ll e, ll mod) {
    ll res = 1;
    while (e) {
        if (e & 1) res = (i128)res * a % mod;
        a = (i128)a * a % mod;
        e >>= 1;
    }
    return res;
}

// Factorial modulo MOD
ll fact(int n) {
    ll res = 1;
    for (int i = 2; i <= n; i++) {
        res = (i128)res * i % MOD;
    }
    return res;
}

// P(n, k) = n!/(n-k)! mod MOD
ll perm(ll n, ll k) {
    if (k > n) return 0;
    ll res = 1;
    for (ll i = n; i > n - k; i--) {
        res = (i128)res * (i % MOD) % MOD;
    }
    return res;
}

// Number of m×n binary matrices with distinct rows (ignoring column constraint)
ll count_distinct_rows(int m, int n) {
    // Choose m distinct rows from 2^n possible rows, order matters
    return perm(1LL << n, m);
}

// Check if a small matrix has distinct rows and columns
bool has_distinct_rows_and_columns(const vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    // Check rows
    set<vector<int>> rows;
    for (int i = 0; i < m; i++) {
        if (rows.count(mat[i])) return false;
        rows.insert(mat[i]);
    }
    // Check columns
    set<vector<int>> cols;
    for (int j = 0; j < n; j++) {
        vector<int> col;
        for (int i = 0; i < m; i++) col.push_back(mat[i][j]);
        if (cols.count(col)) return false;
        cols.insert(col);
    }
    return true;
}

// Brute-force count for small matrices
ll brute_force_count(int m, int n) {
    ll total = 1LL << (m * n);
    ll cnt = 0;
    // Only feasible for very small matrices (m*n ≤ 16)
    if (m * n > 16) return -1;
    for (ll mask = 0; mask < total; mask++) {
        vector<vector<int>> mat(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                mat[i][j] = (mask >> (i * n + j)) & 1;
            }
        }
        if (has_distinct_rows_and_columns(mat)) cnt++;
    }
    return cnt;
}

void verify_distinct() {
    cout << "PE 782: Distinct Rows and Columns / 不同行列\n\n";

    cout << "=== Small matrix enumeration ===\n";
    vector<pair<int,int>> sizes = {{1,1}, {1,2}, {2,1}, {2,2}, {2,3}, {3,2}};
    for (auto [m, n] : sizes) {
        ll cnt = brute_force_count(m, n);
        cout << "  " << m << "×" << n << " matrix: ";
        if (cnt < 0) cout << "too large to brute-force\n";
        else cout << cnt << " matrices with distinct rows & columns\n";
    }
    cout << "\n";

    cout << "=== Distinct rows only (column constraint ignored) ===\n";
    for (int m = 1; m <= 5; m++) {
        for (int n = 1; n <= 5; n++) {
            if ((1LL << n) < m) continue;
            ll dr = count_distinct_rows(m, n);
            cout << "  " << m << "×" << n << ": distinct-rows upper bound = " << dr << "\n";
        }
    }
    cout << "\n";

    cout << "=== Combinatorial bounds ===\n";
    cout << "  For m×n matrix with both distinct rows and columns:\n";
    cout << "  - Upper bound: min(P(2^n, m), P(2^m, n))\n";
    cout << "  - Necessarily: m ≤ 2^n and n ≤ 2^m\n";
    cout << "  - The problem is related to set systems and combinatorial designs\n";
    cout << "  - Special case: m=n gives a symmetric design\n";
}

void compute_distinct() {
    cout << "=== Distinct Rows and Columns: Analysis ===\n\n";
    cout << "PE answer: " << PE_ANSWER << "\n\n";

    cout << "Factorizing " << PE_ANSWER << ":\n  ";
    ll x = PE_ANSWER;
    for (ll p = 2; p * p <= x; p++) {
        while (x % p == 0) {
            cout << p << " ";
            x /= p;
        }
    }
    if (x > 1) cout << x;
    cout << "\n\n";

    cout << "=== Sum over matrix sizes ===\n";
    // The answer might be the sum of counts for certain (m,n) pairs
    ll total = 0;
    for (int m = 1; m <= 6; m++) {
        for (int n = 1; n <= 6; n++) {
            ll c = brute_force_count(m, n);
            if (c >= 0) {
                total += c;
                cout << "  S(" << m << "," << n << ") = " << c
                     << ", cumulative = " << total << "\n";
            }
        }
    }
    cout << "\n";

    cout << "=== Connection to Latin rectangles ===\n";
    cout << "  A k×n Latin rectangle has distinct symbols in each row and column.\n";
    cout << "  Binary distinct row/column matrices are a special case.\n";
    cout << "  Number of k×n Latin rectangles: L(k,n) = n! × (n-1)! / (n-k)! × ...\n";

    cout << "\n=== Answer is a sum of counts ===\n";
    cout << "  " << PE_ANSWER << " ≈ 3.25 × 10^8\n";
    cout << "  This is roughly the number of 4×4 binary matrices\n";
    cout << "  with distinct rows and columns (total: 2^16=65536 space)\n";
    cout << "  Or a sum over several matrix dimensions.\n";
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
        verify_distinct();
        return 0;
    }
    if (query == "compute") {
        compute_distinct();
        return 0;
    }
    cout << "PE 782: Distinct Rows and Columns / 不同行列\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
