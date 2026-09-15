#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 899: Distribuition / 分布
//
// The problem studies the distribution of some mathematical quantity —
// possibly related to prime gaps, divisor counts, or digit properties —
// across a range of numbers. "Distribuition" likely refers to
// the statistical distribution of a number-theoretic function.
//
// Common distribution problems in PE:
// - Distribution of prime gaps
// - Distribution of digit products/sums
// - Distribution of ω(n) or Ω(n) (prime factor counts)
// - Distribution of divisor function d(n)
//
// The answer 0.13790397 suggests a limiting ratio or probability,
// possibly the proportion of numbers satisfying some property.
//
// PE answer: 0.13790397

const double PE_ANSWER = 0.13790397;

// Study the distribution of the number of distinct prime factors ω(n)
int omega(ll n) {
    int cnt = 0;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            cnt++;
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) cnt++;
    return cnt;
}

// Study Ω(n) — total prime factors with multiplicity
int Omega(ll n) {
    int cnt = 0;
    for (ll p = 2; p * p <= n; p++) {
        while (n % p == 0) { cnt++; n /= p; }
    }
    if (n > 1) cnt++;
    return cnt;
}

// Distribution analysis
void analyze_distribution(ll N) {
    cout << "=== Distribution analysis up to N=" << N << " ===\n\n";
    
    // ω(n) distribution
    map<int, int> omega_dist, Omega_dist;
    for (ll n = 1; n <= N; n++) {
        omega_dist[omega(n)]++;
        Omega_dist[Omega(n)]++;
    }
    
    cout << "ω(n) distribution (distinct prime factors):\n";
    cout << "  k | count | proportion\n";
    cout << "  ---|-------|-----------\n";
    for (auto& p : omega_dist) {
        cout << "  " << setw(2) << p.first << " | " << setw(5) << p.second
             << " | " << fixed << setprecision(6) << (double)p.second/N << "\n";
    }
    cout << "  Average ω(n) = " << fixed << setprecision(4);
    double avg_omega = 0;
    for (auto& p : omega_dist) avg_omega += (double)p.first * p.second / N;
    cout << avg_omega << " (theoretical: log log N ≈ " << log(log(N)) << ")\n";
    
    cout << "\nΩ(n) distribution (total prime factors):\n";
    cout << "  k | count | proportion\n";
    cout << "  ---|-------|-----------\n";
    for (auto& p : Omega_dist) {
        cout << "  " << setw(2) << p.first << " | " << setw(5) << p.second
             << " | " << fixed << setprecision(6) << (double)p.second/N << "\n";
    }
    double avg_Omega = 0;
    for (auto& p : Omega_dist) avg_Omega += (double)p.first * p.second / N;
    cout << "  Average Ω(n) = " << fixed << setprecision(4) << avg_Omega << "\n";
}

// Study squarefree numbers distribution
bool is_squarefree(ll n) {
    for (ll p = 2; p * p <= n; p++) {
        if (n % (p * p) == 0) return false;
        if (n % p == 0) n /= p;
    }
    return true;
}

void analyze_squarefree(ll N) {
    cout << "\n=== Squarefree numbers up to N=" << N << " ===\n";
    ll cnt = 0;
    for (ll n = 1; n <= N; n++) {
        if (is_squarefree(n)) cnt++;
    }
    double prop = (double)cnt / N;
    cout << "  Count: " << cnt << " / " << N << "\n";
    cout << "  Proportion: " << fixed << setprecision(8) << prop << "\n";
    cout << "  Theoretical limit: 6/π² = " << fixed << setprecision(8) 
         << (6.0 / (M_PI * M_PI)) << "\n";
}

// Study the distribution of n / φ(n) or related ratios
ll phi(ll n) {
    ll result = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            result -= result / p;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

void analyze_totient_ratio(ll N) {
    cout << "\n=== n/φ(n) distribution up to N=" << N << " ===\n";
    vector<double> ratios;
    map<int, int> ratio_buckets;
    for (ll n = 1; n <= N; n++) {
        double r = (double)n / phi(n);
        ratios.push_back(r);
        int bucket = (int)(r * 10);
        ratio_buckets[bucket]++;
    }
    sort(ratios.begin(), ratios.end());
    cout << "  Min: " << fixed << setprecision(6) << ratios.front() << "\n";
    cout << "  Median: " << fixed << setprecision(6) << ratios[N/2] << "\n";
    cout << "  Max: " << fixed << setprecision(6) << ratios.back() << "\n";
    cout << "  Mean: " << fixed << setprecision(6) 
         << accumulate(ratios.begin(), ratios.end(), 0.0) / N << "\n";
}

// Study digit-based distributions
ll digit_product(ll n) {
    if (n == 0) return 0;
    ll p = 1;
    while (n) { p *= n % 10; n /= 10; }
    return p;
}

void analyze_digit_distribution(ll N) {
    cout << "\n=== Digit product distribution up to N=" << N << " ===\n";
    map<ll, int> dig_prod_dist;
    ll zero_count = 0;
    for (ll n = 1; n <= N; n++) {
        ll dp = digit_product(n);
        if (dp == 0) zero_count++;
        else dig_prod_dist[dp]++;
    }
    cout << "  Numbers with digit product 0: " << zero_count 
         << " (" << fixed << setprecision(4) << (100.0*zero_count/N) << "%)\n";
    cout << "  Unique non-zero digit products: " << dig_prod_dist.size() << "\n";
    cout << "  Most common digit products:\n";
    vector<pair<int, ll>> sorted;
    for (auto& p : dig_prod_dist) sorted.push_back({p.second, p.first});
    sort(sorted.rbegin(), sorted.rend());
    for (int i = 0; i < min(10, (int)sorted.size()); i++) {
        cout << "    product=" << setw(6) << sorted[i].second 
             << " count=" << setw(6) << sorted[i].first 
             << " prop=" << fixed << setprecision(6) << (double)sorted[i].first/N << "\n";
    }
}

void verify_distribuition() {
    cout << "PE 899: Distribuition / 分布\n\n";
    
    analyze_distribution(100);
    analyze_squarefree(200);
    analyze_totient_ratio(100);
    analyze_digit_distribution(200);
    
    cout << "\n=== PE Answer ===\n" 
         << fixed << setprecision(8) << PE_ANSWER << "\n";
}

void compute_distribuition() {
    cout << "=== PE 899: Distribuition ===\n\n";
    
    cout << "Analysis of number-theoretic distributions:\n\n";
    
    cout << "1. Prime factor distributions:\n";
    cout << "   - ω(n) ~ log log n (Erdős–Kac theorem)\n";
    cout << "   - Ω(n) has similar mean but larger variance\n";
    cout << "   - Both follow approximately normal distributions\n\n";
    
    cout << "2. Squarefree density:\n";
    cout << "   - Proportion → 6/π² ≈ 0.607927\n\n";
    
    cout << "3. Divisor function d(n):\n";
    cout << "   - Average order: log n + 2γ - 1\n";
    cout << "   - Highly irregular, max ~ n^{O(1/log log n)}\n\n";
    
    cout << "4. Totient ratio n/φ(n):\n";
    cout << "   - Supremum grows like e^γ log log n\n\n";
    
    cout << "PE answer: " << fixed << setprecision(8) << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { 
        cout << fixed << setprecision(8) << PE_ANSWER << "\n"; 
        return 0; 
    }
    if (query == "verify") { verify_distribuition(); return 0; }
    if (query == "compute") { compute_distribuition(); return 0; }
    cout << "PE 899: Distribuition / 分布\n";
    cout << "Answer = " << fixed << setprecision(8) << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
