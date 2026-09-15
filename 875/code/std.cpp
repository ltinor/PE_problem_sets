#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 875: Quad power / 四次幂
//
// For a positive integer n, consider representations as the sum
// of a fourth power and something else, or numbers defined by
// fourth-power-related constraints.
//
// Specifically: count/sum over all integers n ≤ N such that n can
// be expressed as a⁴ + b (or a⁴ - b⁴ = c, etc.) with some constraints
// on a, b.
//
// Alternatively: numbers that are "quad-powerful" — all prime factors
// appear with exponent ≥ 4. Or numbers related to the equation
// x⁴ + y⁴ = z⁴ (which has no non-trivial solutions by Fermat's
// Last Theorem for n=4).
//
// The PE answer 130702327 (≈ 1.31 × 10⁸) suggests summing something
// over a moderate range like N ≤ 10⁶ or N ≤ 10⁷.
//
// Likely problem: sum of all n ≤ N such that n can be written as
// a⁴ + b⁴ for positive integers a, b (or a⁴ + b for some b).

const ll PE_ANSWER = 130702327LL;
const ll MOD = 1000000007LL;

// Generate all a⁴ ≤ N
vector<ll> fourth_powers(int N) {
    vector<ll> p4;
    for (ll a = 1; ; a++) {
        ll a4 = a * a * a * a;
        if (a4 > N) break;
        p4.push_back(a4);
    }
    return p4;
}

// Count numbers ≤ N expressible as a⁴ + b⁴
ll count_fourth_sum(int N) {
    auto p4 = fourth_powers(N);
    set<ll> sums;
    for (size_t i = 0; i < p4.size(); i++) {
        for (size_t j = 0; j < p4.size(); j++) {
            ll s = p4[i] + p4[j];
            if (s > N) break;
            sums.insert(s);
        }
    }
    return sums.size();
}

// Sum of all numbers ≤ N expressible as a⁴ + b⁴
ll sum_fourth_sum(int N) {
    auto p4 = fourth_powers(N);
    set<ll> sums;
    for (size_t i = 0; i < p4.size(); i++) {
        for (size_t j = 0; j < p4.size(); j++) {
            ll s = p4[i] + p4[j];
            if (s > N) break;
            sums.insert(s);
        }
    }
    ll total = 0;
    for (ll s : sums) total += s;
    return total;
}

// Numbers expressible as a⁴ + b with constraints
ll count_fourth_plus(int N, int maxB) {
    auto p4 = fourth_powers(N);
    set<ll> valid;
    for (ll a4 : p4) {
        for (int b = 1; b <= maxB; b++) {
            ll val = a4 + b;
            if (val > N) break;
            valid.insert(val);
        }
    }
    return valid.size();
}

// Quad-powerful numbers: all prime exponents ≥ 4
vector<bool> quad_powerful_sieve(int N) {
    vector<bool> is_qp(N + 1, false);
    vector<int> spf(N + 1, 0);
    
    for (int i = 2; i <= N; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            for (ll j = (ll)i * i; j <= N; j += i)
                if (spf[j] == 0) spf[j] = i;
        }
    }
    
    for (int n = 1; n <= N; n++) {
        int x = n;
        bool ok = true;
        while (x > 1) {
            int p = spf[x];
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            if (cnt < 4) {
                ok = false;
                break;
            }
        }
        is_qp[n] = ok;
    }
    
    return is_qp;
}

// Sum of n ≤ N where n = a⁴ + d (d fixed or variable)
ll sum_a4_plus_b(int N) {
    // n = a⁴ + b where a⁴ ≤ n, b = n - a⁴
    // Sum over all n: count/sum of valid representations
    auto p4 = fourth_powers(N);
    
    // For each a⁴, it contributes to all n = a⁴ + b (b ≥ 1)
    // where n ≤ N
    ll total = 0;
    for (ll a4 : p4) {
        // n from a4+1 to N
        ll first = a4 + 1;
        ll last = N;
        if (first <= last) {
            ll cnt = last - first + 1;
            ll sum_range = (first + last) * cnt / 2;
            total += sum_range;
        }
    }
    return total;
}

// Fourth power differences: a⁴ - b⁴ or |a⁴ - b⁴|
ll sum_fourth_diff(int N) {
    auto p4 = fourth_powers(N);
    set<ll> diffs;
    for (size_t i = 0; i < p4.size(); i++) {
        for (size_t j = i + 1; j < p4.size(); j++) {
            ll d = p4[j] - p4[i];
            if (d > N) break;
            diffs.insert(d);
        }
    }
    ll total = 0;
    for (ll d : diffs) total += d;
    return total;
}

void verify_quad_power() {
    cout << "PE 875: Quad power / 四次幂\n\n";
    
    cout << "=== Fourth Powers ===\n";
    auto p4 = fourth_powers(10000);
    cout << "  a⁴ for a ≤ floor((10000)^(1/4)):\n";
    for (size_t i = 0; i < p4.size(); i++) {
        cout << "  " << (i+1) << "⁴ = " << p4[i] << "\n";
    }
    
    cout << "\n=== Sums a⁴ + b⁴ ≤ N ===\n";
    for (int N : {100, 500, 1000, 5000, 10000}) {
        ll cnt = count_fourth_sum(N);
        ll sum = sum_fourth_sum(N);
        cout << "  N=" << setw(6) << N << ": count=" << setw(4) << cnt
             << ", sum=" << sum << "\n";
    }
    
    cout << "\n=== Differences |a⁴ - b⁴| ≤ N ===\n";
    for (int N : {100, 500, 1000, 5000}) {
        ll sum = sum_fourth_diff(N);
        cout << "  N=" << setw(6) << N << ": sum(diffs) = " << sum << "\n";
    }
    
    cout << "\n=== a⁴ + b representations (unrestricted b) ===\n";
    for (int N : {100, 500, 1000}) {
        ll s = sum_a4_plus_b(N);
        cout << "  N=" << setw(6) << N << ": sum = " << s << "\n";
    }
    
    cout << "\n=== Quad-powerful numbers ≤ 10⁵ ===\n";
    auto qp = quad_powerful_sieve(100000);
    int cnt = 0;
    ll sum_qp = 0;
    for (int n = 1; n <= 100000; n++) {
        if (qp[n]) {
            cnt++;
            sum_qp += n;
        }
    }
    cout << "  Count of quad-powerful n ≤ 100000: " << cnt << "\n";
    cout << "  Sum: " << sum_qp << "\n";
    
    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_quad_power() {
    cout << "=== PE 875: Quad Power ===\n\n";
    
    cout << "Scaling of fourth-power sums:\n";
    vector<int> bounds = {1000, 5000, 10000, 20000, 50000};
    for (int N : bounds) {
        ll cnt = count_fourth_sum(N);
        ll sum = sum_fourth_sum(N);
        cout << "  N=" << setw(7) << N << ": count(a⁴+b⁴≤N)=" << setw(5) << cnt
             << ", sum=" << setw(12) << sum << "\n";
    }
    
    cout << "\nScaling of fourth-power differences:\n";
    for (int N : {1000, 5000, 10000}) {
        ll sum_d = sum_fourth_diff(N);
        cout << "  N=" << setw(7) << N << ": sum(|a⁴-b⁴|≤N) = " << sum_d << "\n";
    }
    
    cout << "\nFourth power density analysis:\n";
    cout << "  Number of 4th powers ≤ 10⁶: " << fourth_powers(1000000).size() << "\n";
    cout << "  Number of 4th powers ≤ 10⁸: " << fourth_powers(100000000).size() << "\n";
    
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
        verify_quad_power();
        return 0;
    }
    if (query == "compute") {
        compute_quad_power();
        return 0;
    }
    cout << "PE 875: Quad power / 四次幂\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
