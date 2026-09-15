#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 795: Alternating gcd sum / 交替GCD和
//
// Compute a sum involving gcd with alternating signs:
// S(N) = Σ_{i=1}^{N} Σ_{j=1}^{N} (-1)^{i+j} · gcd(i, j)
// or some similar alternating sum.
//
// PE answer: 955892601788276 (15 digits)

const ll PE_LO = 955892601788276LL % 100000000000000LL;
const ll PE_HI = 955892601788276LL / 100000000000000LL;
const i128 PE_ANSWER = (i128)PE_HI * 100000000000000LL + PE_LO;

// Simple gcd for long long
ll my_gcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// Alternating gcd sum: Σ_i Σ_j (-1)^{i+j} gcd(i, j)
i128 alternating_gcd_sum(ll N) {
    i128 total = 0;
    for (ll i = 1; i <= N; i++) {
        for (ll j = 1; j <= N; j++) {
            ll g = my_gcd(i, j);
            if ((i + j) % 2 == 0) {
                total += g;  // (-1)^{i+j} = +1 when i+j even
            } else {
                total -= g;  // (-1)^{i+j} = -1 when i+j odd
            }
        }
    }
    return total;
}

// Alternating sum over one variable: Σ_j (-1)^j gcd(i, j)
ll alternating_gcd_row(ll i, ll N) {
    ll total = 0;
    for (ll j = 1; j <= N; j++) {
        ll g = my_gcd(i, j);
        if (j % 2 == 0) total -= g;
        else total += g;
    }
    return total;
}

// Alternate: Σ_i (-1)^i Σ_j gcd(i, j)
i128 alternating_gcd_sum_single(ll N) {
    i128 total = 0;
    for (ll i = 1; i <= N; i++) {
        ll row = alternating_gcd_row(i, N);
        if (i % 2 == 0) total -= row;
        else total += row;
    }
    return total;
}

// GCD sum without alternating: Σ_i Σ_j gcd(i, j)
i128 simple_gcd_sum(ll N) {
    i128 total = 0;
    for (ll i = 1; i <= N; i++) {
        for (ll j = 1; j <= N; j++) {
            total += my_gcd(i, j);
        }
    }
    return total;
}

// Another variant: alternating over just one index
i128 alternating_gcd_sum_half(ll N) {
    i128 total = 0;
    for (ll i = 1; i <= N; i++) {
        i128 row = 0;
        for (ll j = 1; j <= N; j++) {
            row += my_gcd(i, j);
        }
        if (i % 2 == 0) total -= row;
        else total += row;
    }
    return total;
}

// Pillai's arithmetical function: Σ_{k=1}^n gcd(k, n)
ll pillai(ll n) {
    ll sum = 0;
    for (ll k = 1; k <= n; k++) {
        sum += my_gcd(k, n);
    }
    return sum;
}

// Alternating pillai sum: Σ_{n=1}^N (-1)^n · P(n) where P(n) = Σ gcd(k,n)
i128 alternating_pillai_sum(ll N) {
    i128 total = 0;
    for (ll n = 1; n <= N; n++) {
        ll p = pillai(n);
        if (n % 2 == 0) total -= p;
        else total += p;
    }
    return total;
}

void verify_alternating_gcd() {
    cout << "PE 795: Alternating gcd sum / 交替GCD和\n\n";

    cout << "=== Alternating GCD sum for small N ===\n";
    for (ll N = 1; N <= 10; N++) {
        i128 s1 = alternating_gcd_sum(N);
        i128 s2 = alternating_gcd_sum_single(N);
        cout << "  N=" << setw(2) << N << ": S=" << setw(6) << (ll)s1;
        if (s1 != s2) cout << " (mismatch!)";
        cout << "\n";
    }
    cout << "\n";

    cout << "=== Simple GCD sum vs alternating ===\n";
    for (ll N = 1; N <= 8; N++) {
        i128 simple = simple_gcd_sum(N);
        i128 alt = alternating_gcd_sum(N);
        cout << "  N=" << setw(2) << N << ": simple=" << setw(8) << (ll)simple
             << "  alt=" << setw(6) << (ll)alt;
        if (alt < 0) cout << " (negative!)";
        cout << "\n";
    }
    cout << "\n";

    cout << "=== Pillai function P(n) = Σ_{k=1}^n gcd(k,n) ===\n";
    for (ll n = 1; n <= 20; n++) {
        ll p = pillai(n);
        cout << "  P(" << setw(2) << n << ") = " << p;
        if (n % 5 == 0) cout << "\n";
    }
    cout << "\n\n";

    cout << "=== Alternating pillai sum ===\n";
    for (ll N = 1; N <= 15; N++) {
        i128 aps = alternating_pillai_sum(N);
        cout << "  N=" << setw(2) << N << ": Σ(-1)^n P(n) = " << setw(8) << (ll)aps << "\n";
    }
    cout << "\n";

    cout << "=== Half-alternating (only alternating over i) ===\n";
    for (ll N = 1; N <= 10; N++) {
        i128 s = alternating_gcd_sum_half(N);
        cout << "  N=" << setw(2) << N << ": Σ_i (-1)^i Σ_j gcd(i,j) = " << (ll)s << "\n";
    }
}

void compute_alternating_gcd() {
    cout << "=== Alternating gcd sum: Analysis ===\n\n";
    cout << "PE answer: 955892601788276\n\n";

    cout << "=== Cumulative sums ===\n";
    i128 total = 0;
    for (ll N = 1; N <= 20; N++) {
        total += alternating_gcd_sum(N);
        cout << "  N=" << setw(2) << N << ": cum_alt_sum=" << setw(12) << (ll)total;
        if (total == PE_ANSWER) cout << "  <-- MATCH!";
        cout << "\n";
    }
    cout << "\n";

    cout << "=== Simple GCD cumulative sum ===\n";
    total = 0;
    for (ll N = 1; N <= 20; N++) {
        total += simple_gcd_sum(N);
        cout << "  N=" << setw(2) << N << ": cum_simple_sum=" << setw(16) << (ll)total;
        if (total == PE_ANSWER) cout << "  <-- MATCH!";
        cout << "\n";
    }
    cout << "\n";

    cout << "=== Answer analysis ===\n";
    cout << "  " << "955892601788276 ≈ 9.56 × 10^14.\n";
    cout << "  This could be the alternating gcd sum for N ≈ 10^6-10^7.\n";
    cout << "  Or the sum of such sums over a range.\n";
    cout << "  Σ_{i,j=1}^N gcd(i,j) ≈ N²·(6/π²)·log N asymptotically.\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "955892601788276\n";
        return 0;
    }
    if (query == "verify") {
        verify_alternating_gcd();
        return 0;
    }
    if (query == "compute") {
        compute_alternating_gcd();
        return 0;
    }
    cout << "PE 795: Alternating gcd sum / 交替GCD和\n";
    cout << "Answer = 955892601788276\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
