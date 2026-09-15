#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
using ld = long double;

// Binomial coefficient
i128 C[15][15];
void init_comb() {
    for (int i = 0; i <= 12; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
}

i128 compute_u(int j, int N) {
    i128 val = 0, p = 1;
    for (int t = 0; t <= N; t++) {
        if (t % 2 == 0) val += p; else val -= p;
        p *= j;
    }
    return val;
}

// Brute force: Lagrange interpolation via solving linear system
// For k points (i, u_i), i=1..k, fit degree k-1 polynomial P(x)
// P(x) = sum_{j=0}^{k-1} c_j * x^j
// Solve Vandermonde system using Gaussian elimination with fractions
// Then evaluate P(k+1)

struct Frac {
    i128 num, den;
    Frac(i128 n = 0, i128 d = 1) : num(n), den(d) { reduce(); }
    static i128 mygcd(i128 a, i128 b) {
        a = a < 0 ? -a : a;
        while (b) { i128 t = b; b = a % b; a = t; }
        return a;
    }
    void reduce() {
        if (den < 0) { num = -num; den = -den; }
        if (num == 0) { den = 1; return; }
        i128 g = mygcd(num, den);
        num /= g; den /= g;
    }
};

Frac operator+(Frac a, Frac b) { return Frac(a.num*b.den + b.num*a.den, a.den*b.den); }
Frac operator-(Frac a, Frac b) { return Frac(a.num*b.den - b.num*a.den, a.den*b.den); }
Frac operator*(Frac a, Frac b) { return Frac(a.num*b.num, a.den*b.den); }
Frac operator/(Frac a, Frac b) { return Frac(a.num*b.den, a.den*b.num); }

// Gaussian elimination on augmented matrix [A|b], n equations, n unknowns
vector<Frac> solve(vector<vector<Frac>> A, vector<Frac> b) {
    int n = A.size();
    for (int col = 0; col < n; col++) {
        // Find pivot
        int pivot = col;
        while (pivot < n && A[pivot][col].num == 0) pivot++;
        if (pivot == n) continue;
        swap(A[col], A[pivot]);
        swap(b[col], b[pivot]);
        Frac piv = A[col][col];
        for (int j = col; j < n; j++) A[col][j] = A[col][j] / piv;
        b[col] = b[col] / piv;
        for (int i = 0; i < n; i++) {
            if (i == col) continue;
            Frac factor = A[i][col];
            for (int j = col; j < n; j++) A[i][j] = A[i][j] - factor * A[col][j];
            b[i] = b[i] - factor * b[col];
        }
    }
    return b;
}

i128 brute_fit(int k, int N) {
    // Build Vandermonde: P(i) = u_i for i=1..k
    // P(x) = c_0 + c_1*x + ... + c_{k-1}*x^{k-1}
    vector<vector<Frac>> A(k, vector<Frac>(k));
    vector<Frac> b_vec(k);
    for (int i = 1; i <= k; i++) {
        i128 xi = 1;
        for (int j = 0; j < k; j++) {
            A[i-1][j] = Frac(xi);
            xi *= i;
        }
        b_vec[i-1] = Frac(compute_u(i, N));
    }
    auto coef = solve(A, b_vec);
    // Evaluate at x = k+1
    Frac result;
    i128 xp = 1;
    for (int j = 0; j < k; j++) {
        result = result + coef[j] * Frac(xp);
        xp *= (k + 1);
    }
    // Result should be integer
    return result.num / result.den;
}

void print_i128(i128 x) {
    if (x == 0) { cout << "0"; return; }
    if (x < 0) { cout << "-"; x = -x; }
    string s;
    while (x > 0) { s += char('0' + (x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init_comb();

    int N;
    cin >> N;

    i128 ans = 0;
    for (int k = 1; k <= N; k++) {
        ans += brute_fit(k, N);
    }

    print_i128(ans);
    cout << "\n";
    return 0;
}
