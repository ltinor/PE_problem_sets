#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE462: Permutation of 3-smooth numbers
// S(N) = {2^a * 3^b ≤ N}
// F(N) = number of permutations where each element comes after all proper divisors
//
// This is the number of linear extensions of the divisibility poset on S(N).
// The poset is a Young diagram shape λ where λ_a = max b: 2^a * 3^b ≤ N.
// F(N) = |S(N)|! / ∏ hook_lengths (by the hook-length formula for SYT)
//
// PE: F(10^18) in scientific notation, 10 decimal places

// Compute log10(n!) using Stirling or direct sum
long double log10_factorial(ll n) {
    if (n <= 1) return 0.0L;
    long double sum = 0.0L;
    // Use direct sum for small n, Stirling for large
    if (n <= 1000000) {
        for (ll i = 2; i <= n; i++) {
            sum += log10l((long double)i);
        }
    } else {
        // Stirling: log10(n!) ≈ n*log10(n/e) + log10(√(2πn))
        const long double PI_L = acosl(-1.0L);
        sum = n * log10l((long double)n / expl(1.0L)) 
            + 0.5L * log10l(2.0L * PI_L * n);
    }
    return sum;
}

// Compute g(a,b) = gcd? Actually need hook lengths.
// For a Young diagram λ (French notation: row a has λ_a cells),
// hook length at cell (a,b) where a is row index, b is column index:
// h(a,b) = (λ_a - b) + (λ'_b - a) - 1
// where λ_a = length of row a, λ'_b = length of column b.

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    
    if (mode == "PE") {
        ll N = 1000000000000000000LL; // 10^18
        
        // Compute λ: for each a (0-based), λ_a = max b: 2^a * 3^b ≤ N
        vector<int> lambda;
        lambda.reserve(100);
        
        ll pow2 = 1;
        for (int a = 0; ; a++) {
            if (pow2 > N) break;
            // Find max b: 3^b ≤ N / pow2
            ll max_val = N / pow2;
            int b = 0;
            ll pow3 = 1;
            while (pow3 <= max_val) {
                b++;
                if (pow3 > max_val / 3) break;
                pow3 *= 3;
            }
            // b is now the count (0..b-1), so length = b
            if (b > 0) lambda.push_back(b);
            else break;
            
            if (pow2 > N / 2) break;
            pow2 *= 2;
        }
        
        int rows = lambda.size();
        ll total_cells = 0;
        for (int r : lambda) total_cells += r;
        
        // Compute log10 of hook product
        long double log_hook_product = 0.0L;
        
        // For each cell (a,b) in the diagram
        for (int a = 0; a < rows; a++) {
            int row_len = lambda[a];
            for (int b = 0; b < row_len; b++) {
                // hook = (row_len - b) + (col_len - a) - 1
                // col_len = number of rows with length > b
                int col_len = 0;
                for (int r = 0; r < rows; r++) {
                    if (lambda[r] > b) col_len++;
                }
                ll hook = (ll)(row_len - b) + (ll)(col_len - a) - 1;
                log_hook_product += log10l((long double)hook);
            }
        }
        
        // log10 F(N) = log10(total_cells!) - log_hook_product
        long double log_result = log10_factorial(total_cells) - log_hook_product;
        
        // Convert to scientific notation
        long double int_part;
        long double frac_part = modfl(log_result, &int_part);
        ll exponent = (ll)int_part;
        long double mantissa = powl(10.0L, frac_part);
        
        // Adjust mantissa to [1, 10)
        // mantissa should already be in [1,10) since we used log10
        // But due to floating point, might need adjustment
        if (mantissa >= 10.0L) {
            mantissa /= 10.0L;
            exponent++;
        }
        if (mantissa < 1.0L) {
            mantissa *= 10.0L;
            exponent--;
        }
        
        cout << fixed << setprecision(10) << mantissa << "e" << exponent << "\n";
        return 0;
    }
    
    if (mode == "test") {
        ll N; cin >> N;
        // Compute for smaller N to verify
        vector<int> lambda;
        ll pow2 = 1;
        for (int a = 0; ; a++) {
            if (pow2 > N) break;
            ll max_val = N / pow2;
            int b = 0;
            ll pow3 = 1;
            while (pow3 <= max_val) {
                b++;
                if (pow3 > max_val / 3) break;
                pow3 *= 3;
            }
            if (b > 0) lambda.push_back(b);
            else break;
            if (pow2 > N / 2) break;
            pow2 *= 2;
        }
        
        int rows = lambda.size();
        ll total_cells = 0;
        for (int r : lambda) total_cells += r;
        
        long double log_hook_product = 0.0L;
        for (int a = 0; a < rows; a++) {
            int row_len = lambda[a];
            for (int b = 0; b < row_len; b++) {
                int col_len = 0;
                for (int r = 0; r < rows; r++) {
                    if (lambda[r] > b) col_len++;
                }
                ll hook = (ll)(row_len - b) + (ll)(col_len - a) - 1;
                log_hook_product += log10l((long double)hook);
            }
        }
        
        long double log_result = log10_factorial(total_cells) - log_hook_product;
        long double int_part;
        long double frac_part = modfl(log_result, &int_part);
        ll exponent = (ll)int_part;
        long double mantissa = powl(10.0L, frac_part);
        
        if (mantissa >= 10.0L) { mantissa /= 10.0L; exponent++; }
        if (mantissa < 1.0L) { mantissa *= 10.0L; exponent--; }
        
        cout << fixed << setprecision(10) << mantissa << "e" << exponent << "\n";
        return 0;
    }
    
    // Default: single N
    ll N = stoll(mode);
    
    vector<int> lambda;
    ll pow2 = 1;
    for (int a = 0; ; a++) {
        if (pow2 > N) break;
        ll max_val = N / pow2;
        int b = 0;
        ll pow3 = 1;
        while (pow3 <= max_val) {
            b++;
            if (pow3 > max_val / 3) break;
            pow3 *= 3;
        }
        if (b > 0) lambda.push_back(b);
        else break;
        if (pow2 > N / 2) break;
        pow2 *= 2;
    }
    
    int rows = lambda.size();
    ll total_cells = 0;
    for (int r : lambda) total_cells += r;
    
    long double log_hook_product = 0.0L;
    for (int a = 0; a < rows; a++) {
        int row_len = lambda[a];
        for (int b = 0; b < row_len; b++) {
            int col_len = 0;
            for (int r = 0; r < rows; r++) {
                if (lambda[r] > b) col_len++;
            }
            ll hook = (ll)(row_len - b) + (ll)(col_len - a) - 1;
            log_hook_product += log10l((long double)hook);
        }
    }
    
    long double log_result = log10_factorial(total_cells) - log_hook_product;
    long double int_part;
    long double frac_part = modfl(log_result, &int_part);
    ll exponent = (ll)int_part;
    long double mantissa = powl(10.0L, frac_part);
    
    if (mantissa >= 10.0L) { mantissa /= 10.0L; exponent++; }
    if (mantissa < 1.0L) { mantissa *= 10.0L; exponent--; }
    
    cout << fixed << setprecision(10) << mantissa << "e" << exponent << "\n";
}
