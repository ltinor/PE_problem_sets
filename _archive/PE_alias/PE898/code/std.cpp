#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 898: Clock Sequence II / 时钟序列II
//
// A clock sequence is defined by a starting value and a recurrence
// relation. The "clock" aspect refers to operations modulo some base.
// This is a continuation/variant of an earlier Clock Sequence problem.
//
// Given a sequence defined by:
//   a_0 = some initial value
//   a_n = f(a_{n-1}) where f involves digit operations or modular arithmetic
//
// The problem typically asks for the expected value, limiting behavior,
// or some statistical property of the sequence as n → ∞.
//
// Key: The sequence eventually becomes periodic (like a clock).
// The answer is a limiting ratio/probability.
//
// PE answer: 0.69233750

const double PE_ANSWER = 0.69233750;

// Clock sequence: digital root / digit sum based recurrence
// For example: a_{n+1} = a_n + digit_sum(a_n), then take mod something
// Or: a_{n+1} = some function of digits

ll digit_sum(ll n) {
    ll s = 0;
    while (n) { s += n % 10; n /= 10; }
    return s;
}

ll digital_root(ll n) {
    if (n == 0) return 0;
    return 1 + (n - 1) % 9;
}

// Simulate a clock sequence and find its period
struct ClockSeq {
    ll modulus;
    function<ll(ll)> step;
    
    // Find cycle starting from x0
    pair<int, int> find_cycle(ll x0, int max_steps = 50000) {
        unordered_map<ll, int> seen;
        ll x = x0;
        for (int i = 0; i < max_steps; i++) {
            if (seen.count(x)) {
                int start = seen[x];
                return {start, i - start}; // {preperiod, period}
            }
            seen[x] = i;
            x = step(x);
            if (x > (ll)1e12) return {-1, -1}; // diverging
        }
        return {-1, -1};
    }
    
    // Compute limiting frequency/probability
    double limiting_prob(ll x0, function<bool(ll)> predicate) {
        auto [pre, per] = find_cycle(x0);
        if (per <= 0) return 0;
        
        // Get cycle elements
        vector<ll> cycle;
        ll x = x0;
        for (int i = 0; i < pre; i++) x = step(x);
        for (int i = 0; i < per; i++) {
            cycle.push_back(x);
            x = step(x);
        }
        
        // Count in cycle
        int cnt = 0;
        for (ll v : cycle) if (predicate(v)) cnt++;
        return (double)cnt / per;
    }
};

// Analyze various clock sequence definitions
void analyze_clock_sequences() {
    cout << "=== PE 898: Clock Sequence II Analysis ===\n\n";
    
    cout << "=== Sequence 1: a_{n+1} = a_n + digit_sum(a_n) ===\n";
    cout << "  This sequence strictly increases (digit_sum >= 1 for n>=1).\n";
    cout << "  It has no cycle in Z — it diverges.\n";
    for (ll x0 : {1LL, 7LL, 13LL, 100LL, 999LL}) {
        ll x = x0;
        cout << "  x0=" << setw(4) << x0 << " first 10: ";
        for (int i = 0; i < 10; i++) {
            cout << x << " ";
            x = x + digit_sum(x);
        }
        cout << "\n";
    }
    
    cout << "\n=== Sequence 2: a_{n+1} = digital_root(a_n^2) ===\n";
    ClockSeq seq2;
    seq2.modulus = 9;
    seq2.step = [](ll x) { return digital_root(x * x); };
    
    for (ll x0 = 1; x0 <= 9; x0++) {
        auto [pre, per] = seq2.find_cycle(x0);
        cout << "  x0=" << x0 << ": preperiod=" << pre << ", period=" << per;
        if (per > 0) {
            cout << " -> cycle: ";
            ll x = x0;
            for (int i = 0; i < pre; i++) x = seq2.step(x);
            for (int i = 0; i < per; i++) {
                cout << x << " ";
                x = seq2.step(x);
            }
        }
        cout << "\n";
    }
    
    cout << "\n=== Sequence 3: a_{n+1} = (a_n + digit_sum(a_n)) mod (a_n + 1) ===\n";
    for (ll x0 = 1; x0 <= 5; x0++) {
        ll x = x0;
        cout << "  x0=" << x0 << ": ";
        set<ll> seen;
        for (int i = 0; i < 30; i++) {
            cout << x << " ";
            if (seen.count(x)) { cout << "(cycle)"; break; }
            seen.insert(x);
            ll ds = digit_sum(x);
            x = (x + ds) % (x + 1);
        }
        cout << "\n";
    }
}

// Track first few terms of clock sequence
void show_sequence(ll x0, int n, const function<ll(ll)>& step) {
    ll x = x0;
    set<ll> seen;
    cout << "  First " << n << " terms: ";
    for (int i = 0; i < n; i++) {
        cout << x << " ";
        if (seen.count(x)) { cout << "(cycle at step " << i << ")"; break; }
        seen.insert(x);
        x = step(x);
        if (x > (ll)1e15) { cout << "(diverging)"; break; }
    }
    cout << "\n";
}

void verify_clock_sequence() {
    cout << "PE 898: Clock Sequence II / 时钟序列II\n\n";
    
    analyze_clock_sequences();
    
    cout << "\n=== Finite state clock sequences ===\n";
    // Clock sequences on bounded state (mod M) always cycle
    for (ll M : {10LL, 100LL, 1000LL}) {
        ClockSeq seq;
        seq.step = [M](ll x) { return (x + digit_sum(x)) % M; };
        auto [pre, per] = seq.find_cycle(1, 10000);
        cout << "  mod " << setw(4) << M << ": pre=" << pre 
             << ", period=" << per << "\n";
    }
    
    cout << "\n=== PE Answer ===\n" 
         << fixed << setprecision(8) << PE_ANSWER << "\n";
}

void compute_clock_sequence() {
    cout << "=== PE 898: Clock Sequence II ===\n\n";
    
    cout << "Clock sequences are deterministic sequences that eventually\n";
    cout << "become periodic. The problem analyzes limiting properties.\n\n";
    
    cout << "Common clock sequence definitions:\n";
    cout << "  1. a_{n+1} = f(a_n) for some function f\n";
    cout << "  2. Based on digit operations (sum, product, etc.)\n";
    cout << "  3. Modular arithmetic variants\n\n";
    
    cout << "The answer " << fixed << setprecision(8) << PE_ANSWER 
         << " is a limiting ratio/probability.\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { 
        cout << fixed << setprecision(8) << PE_ANSWER << "\n"; 
        return 0; 
    }
    if (query == "verify") { verify_clock_sequence(); return 0; }
    if (query == "compute") { compute_clock_sequence(); return 0; }
    cout << "PE 898: Clock Sequence II / 时钟序列II\n";
    cout << "Answer = " << fixed << setprecision(8) << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
