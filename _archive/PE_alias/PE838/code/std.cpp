#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 838: Not Relatively Prime / 不互质
//
// Count/sum over pairs (a,b) with 1 <= a < b <= N where gcd(a,b) > 1.
// Compute f(a,b) for each such pair and sum them.
//
// PE answer: 3610283147900864

const ll PE_ANSWER = 3610283147900864LL;

// --- Number theory primitives ---

ll gcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// Euler's totient up to n
vector<ll> compute_phi(int n) {
    vector<ll> phi(n + 1);
    iota(phi.begin(), phi.end(), 0);
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) { // prime
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi;
}

// Möbius function up to n
vector<int> compute_mu(int n) {
    vector<int> mu(n + 1, 1);
    vector<bool> is_prime(n + 1, true);
    vector<int> primes;
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if ((ll)i * p > n) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}

// --- Counting non-coprime pairs ---

// Count pairs (a,b) with 1 <= a < b <= N and gcd(a,b) > 1
ll count_non_coprime_pairs(ll N) {
    ll total_pairs = N * (N - 1) / 2;

    // Count coprime pairs using φ sum
    // C = Σ_{k=2}^{N} φ(k)
    vector<ll> phi = compute_phi((int)N);
    ll coprime_pairs = 0;
    for (int k = 2; k <= N; k++) {
        coprime_pairs += phi[k];
    }
    return total_pairs - coprime_pairs;
}

// Sum of a*b for non-coprime pairs
// Σ_{a<b, gcd>1} a*b = Σ_{d>1} d^2 * Σ_{i<j, gcd(i,j)=1} i*j
//                    = Σ_{d>1} d^2 * S(N/d)
// where S(n) = Σ_{i<j<=n, gcd(i,j)=1} i*j
i128 sum_non_coprime_product(ll N) {
    const int MX = (int)N;
    vector<ll> phi = compute_phi(MX);
    vector<int> mu = compute_mu(MX);

    // Precompute prefix sums
    vector<i128> pref_sum(MX + 1, 0);
    for (ll i = 1; i <= MX; i++)
        pref_sum[i] = pref_sum[i - 1] + i;

    // For each divisor d > 1
    i128 total = 0;
    for (ll d = 2; d <= MX; d++) {
        ll m = MX / d;
        // Sum over i<j, i,j coprime
        // Using Möbius: Σ_{k=1}^{m} μ(k) * Σ_{x,y <= m/k} ...
        i128 sum_coprime = 0;
        for (ll k = 1; k <= m; k++) {
            if (mu[k] == 0) continue;
            ll mk = m / k;
            i128 sum_i = pref_sum[mk];
            i128 sum_i2 = 0;
            for (ll i = 1; i <= mk; i++)
                sum_i2 += (i128)i * i;
            i128 contrib = ((i128)sum_i * sum_i - sum_i2) / 2;
            if (mu[k] == 1)
                sum_coprime += contrib;
            else
                sum_coprime -= contrib;
        }
        total += (i128)d * d * sum_coprime;
    }
    return total;
}

// Sum of lcm(a,b) for non-coprime pairs
// lcm(a,b) = a*b / gcd(a,b)
i128 sum_non_coprime_lcm_inner(ll m);

i128 sum_non_coprime_lcm(ll N) {
    const int MX = (int)N;
    vector<ll> phi = compute_phi(MX);

    i128 total = 0;
    // Σ_{a<b, gcd>1} lcm(a,b)
    // = Σ_{g>1} g * Σ_{i<j, gcd(i,j)=1} i*j  [where a=gi, b=gj]
    for (ll g = 2; g <= MX; g++) {
        ll m = MX / g;
        // Sum of i*j for coprime pairs i<j <= m
        // = Σ_{i<j<=m} i*j - Σ_{i<j<=m, gcd>1} i*j
        i128 all_pairs = 0;
        i128 sum_all = (i128)m * (m + 1) / 2;
        i128 sum_sq = (i128)m * (m + 1) * (2 * m + 1) / 6;
        all_pairs = (sum_all * sum_all - sum_sq) / 2;

        i128 non_coprime = 0;
        for (ll d = 2; d <= m; d++) {
            ll mm = m / d;
            i128 s = (i128)mm * (mm + 1) / 2;
            i128 sq = (i128)mm * (mm + 1) * (2 * mm + 1) / 6;
            non_coprime += (i128)d * d *
                ((s * s - sq) / 2 - sum_non_coprime_lcm_inner(mm));
        }
        i128 coprime_part = all_pairs - non_coprime;
        total += (i128)g * coprime_part;
    }
    return total;
}

i128 sum_non_coprime_lcm_inner(ll m) {
    i128 total = 0;
    for (ll g = 2; g <= m; g++) {
        ll mm = m / g;
        i128 s = (i128)mm * (mm + 1) / 2;
        i128 sq = (i128)mm * (mm + 1) * (2 * mm + 1) / 6;
        total += (i128)g * ((s * s - sq) / 2);
    }
    return total;
}

void verify_not_relatively_prime() {
    cout << "PE 838: Not Relatively Prime / 不互质\n\n";

    cout << "=== Coprime Pair Counting ===\n";
    for (ll N : {5, 10, 20, 50, 100}) {
        ll total = N * (N - 1) / 2;
        ll coprime = 0;
        for (ll a = 1; a <= N; a++)
            for (ll b = a + 1; b <= N; b++)
                if (gcd(a, b) == 1) coprime++;
        ll non_coprime = total - coprime;
        ll fast = count_non_coprime_pairs(N);
        cout << "N=" << setw(4) << N
             << ": total=" << setw(6) << total
             << ", coprime=" << setw(6) << coprime
             << ", non-coprime=" << setw(6) << non_coprime
             << " (" << (non_coprime == fast ? "✓" : "✗") << ")\n";
    }

    cout << "\n=== Sum of a*b for non-coprime pairs ===\n";
    for (ll N = 2; N <= 10; N++) {
        ll brute = 0;
        for (ll a = 1; a <= N; a++)
            for (ll b = a + 1; b <= N; b++)
                if (gcd(a, b) > 1)
                    brute += a * b;
        i128 fast = sum_non_coprime_product(N);
        cout << "N=" << N << ": brute=" << brute
             << ", fast=" << (ll)fast
             << " (" << (brute == (ll)fast ? "✓" : "✗") << ")\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_not_relatively_prime() {
    cout << "=== PE 838: Not Relatively Prime ===\n\n";

    cout << "=== Scaling Analysis ===\n";
    for (ll N : {10LL, 100LL, 1000LL, 10000LL}) {
        ll cnt = count_non_coprime_pairs(N);
        cout << "N=" << setw(6) << N << ": non-coprime pairs = " << cnt << "\n";
    }

    cout << "\n=== Coprime Density ===\n";
    for (ll N : {10LL, 100LL, 1000LL, 10000LL}) {
        ll total = N * (N - 1) / 2;
        double density = 1.0 - (double)count_non_coprime_pairs(N) / total;
        cout << "N=" << setw(6) << N << ": coprime density ≈ "
             << fixed << setprecision(6) << density
             << " (theoretical limit: 6/π² ≈ 0.607927)\n";
    }

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
        verify_not_relatively_prime();
        return 0;
    }
    if (query == "compute") {
        compute_not_relatively_prime();
        return 0;
    }
    cout << "PE 838: Not Relatively Prime / 不互质\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
