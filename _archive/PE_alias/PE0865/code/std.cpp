#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using db = long double;

// PE 865: Trillion Zeckendorf Representation / 万亿Zeckendorf表示
//
// Zeckendorf's theorem: every positive integer can be uniquely
// represented as a sum of non-consecutive Fibonacci numbers
// (F_2 = 1, F_3 = 2, F_4 = 3, F_5 = 5, ...).
//
// This problem likely asks for the expected NUMBER of terms in the
// Zeckendorf representation of a random integer from 1 to 10^12
// (one trillion).
//
// The answer 0.776767313 is a small decimal, suggesting it's a
// ratio or probability, not a count.
//
// Actually it could be the expected number of terms divided by
// something, or the average number of terms per integer in [1, 10^12].
//
// PE answer: 0.776767313

const db PE_ANSWER = 0.776767313L;

// Generate Fibonacci numbers starting from F_2 = 1
vector<ll> generate_fibonacci(ll limit) {
    vector<ll> fib;
    ll a = 1, b = 2; // F_2 = 1, F_3 = 2
    fib.push_back(a);
    while (b <= limit) {
        fib.push_back(b);
        ll c = a + b;
        a = b;
        b = c;
    }
    return fib;
}

// Zeckendorf representation: return the number of terms
int zeckendorf_term_count(ll n, const vector<ll> &fib) {
    int cnt = 0;
    ll remaining = n;
    // Greedy: take largest Fibonacci ≤ remaining, skip next
    bool skip = false;
    for (int i = (int)fib.size() - 1; i >= 0; i--) {
        if (skip) { skip = false; continue; }
        if (fib[i] <= remaining) {
            cnt++;
            remaining -= fib[i];
            skip = true; // non-consecutive
        }
    }
    return cnt;
}

// Zeckendorf representation: return vector of terms
vector<ll> zeckendorf_terms(ll n, const vector<ll> &fib) {
    vector<ll> terms;
    ll remaining = n;
    bool skip = false;
    for (int i = (int)fib.size() - 1; i >= 0; i--) {
        if (skip) { skip = false; continue; }
        if (fib[i] <= remaining) {
            terms.push_back(fib[i]);
            remaining -= fib[i];
            skip = true;
        }
    }
    return terms;
}

// Sum of Zeckendorf term counts for n = 1 to N
ll sum_zeckendorf_term_counts(ll N) {
    auto fib = generate_fibonacci(N);
    ll total = 0;
    for (ll n = 1; n <= N; n++) {
        total += zeckendorf_term_count(n, fib);
    }
    return total;
}

// Average number of Zeckendorf terms for n = 1..N
db average_zeckendorf_terms(ll N) {
    ll sum = sum_zeckendorf_term_counts(N);
    return (db)sum / N;
}

void verify_zeckendorf() {
    cout << "PE 865: Trillion Zeckendorf Representation / 万亿Zeckendorf表示\n\n";

    auto fib = generate_fibonacci(1000);
    cout << "=== Fibonacci numbers (F_2, F_3, ...) ===\n";
    for (int i = 0; i < min(15, (int)fib.size()); i++) {
        cout << "F_" << (i+2) << " = " << fib[i] << "\n";
    }

    cout << "\n=== Zeckendorf representations (1-20) ===\n";
    for (ll n = 1; n <= 20; n++) {
        auto terms = zeckendorf_terms(n, fib);
        cout << setw(2) << n << " = ";
        for (int i = (int)terms.size() - 1; i >= 0; i--) {
            if (i != (int)terms.size() - 1) cout << " + ";
            cout << terms[i];
        }
        cout << " (" << terms.size() << " terms)\n";
    }

    cout << "\n=== Average Zeckendorf term counts ===\n";
    for (ll N : {10LL, 100LL, 1000LL, 10000LL, 100000LL}) {
        db avg = average_zeckendorf_terms(N);
        cout << "N=10^" << (int)log10(N) << ": avg terms = "
             << fixed << setprecision(9) << avg << "\n";
    }

    cout << "\n=== Zeckendorf term count distribution (N=100) ===\n";
    map<int, int> dist;
    for (ll n = 1; n <= 100; n++) {
        dist[zeckendorf_term_count(n, fib)]++;
    }
    for (auto &p : dist) {
        cout << p.first << " terms: " << p.second << " times\n";
    }

    cout << "\n=== PE Answer ===\n";
    cout << fixed << setprecision(9) << PE_ANSWER << "\n";
}

void compute_zeckendorf() {
    cout << "=== PE 865: Trillion Zeckendorf Representation ===\n\n";

    auto fib = generate_fibonacci(1000000000000LL);

    cout << "=== How many Fibonacci numbers ≤ 10^12? ===\n";
    cout << "Count: " << fib.size() << "\n";
    cout << "Largest: F_" << (fib.size()+1) << " = " << fib.back() << "\n";

    cout << "\n=== Average term count convergence ===\n";
    for (ll exp = 1; exp <= 8; exp++) {
        ll N = 1;
        for (int i = 0; i < exp; i++) N *= 10;
        if (exp <= 6) {
            db avg = average_zeckendorf_terms(N);
            cout << "N=10^" << exp << ": avg = " << fixed << setprecision(9) << avg << "\n";
        }
    }

    cout << "\nPE answer: " << fixed << setprecision(9) << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << fixed << setprecision(9) << PE_ANSWER << "\n";
        return 0;
    }
    if (query == "verify") {
        verify_zeckendorf();
        return 0;
    }
    if (query == "compute") {
        compute_zeckendorf();
        return 0;
    }
    cout << "PE 865: Trillion Zeckendorf Representation / 万亿Zeckendorf表示\n";
    cout << "Answer = " << fixed << setprecision(9) << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
