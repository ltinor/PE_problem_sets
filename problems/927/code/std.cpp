#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 927: Prime-ary Tree / 素数多叉树
//
// t_k(n) = # full k-ary trees of height ≤ n
// Recurrence: t_k(0) = 1, t_k(n+1) = 1 + t_k(n)^k
// S_k = {m : m | t_k(n) for some n ≥ 0}
// S = ∩_{p prime} S_p
// R(N) = sum of elements of S ≤ N
//
// For m ∈ S: for every prime p, 0 is reachable from 1 under f_p(x)=1+x^p mod m.
// Using CRT: m ∈ S iff each prime power dividing m is in S.
// Key: S is divisor-closed. Characterize "atoms" of S.
//
// For prime p, the forward orbit of 1 under f(x)=1+x^p mod m must hit 0.
// This imposes strong constraints on m's prime factors.

// We need to find all m ≤ 10^7 such that ∀ prime p, ∃ n: t_p(n) ≡ 0 (mod m).

// Approach: For each candidate m, test against first few primes.
// Then verify pattern for larger primes.

const int MAX_N = 10000000;

// Check if m divides some t_p(n) for a specific prime p
bool divides_t(ll m, int p) {
    if (m == 1) return true;
    ll x = 1 % m;
    set<ll> seen;
    for (int iter = 0; iter < 10000; iter++) {
        if (x == 0) return true;
        if (seen.count(x)) return false;
        seen.insert(x);
        // x = 1 + x^p mod m
        ll xp = 1;
        for (int i = 0; i < p; i++) xp = xp * x % m;
        x = (1 + xp) % m;
    }
    return false; // should not reach here for small m
}

// Check if m ∈ S by testing against several primes
bool in_S(ll m, const vector<int>& test_primes) {
    for (int p : test_primes) {
        if (!divides_t(m, p)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        // Find S elements up to 10^7
        // Based on pattern analysis and verification
        // S consists of numbers whose prime factors are all in a specific set
        
        // Computational verification for small test primes
        vector<int> test_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

        // Systematic search: S is divisor-closed.
        // For each m, if m ∈ S, all divisors of m are also in S.
        // Strategy: find minimal non-trivial elements (atoms), then generate all products
        
        set<ll> S_set;
        S_set.insert(1);
        
        // Search for atoms by checking small primes' divisors
        // Actually, use BFS from known atoms
        vector<ll> atoms;
        
        // Find all m ≤ 10000 that are in S
        for (ll m = 2; m <= 20000; m++) {
            if (in_S(m, test_primes)) {
                // Check if m is an atom (not divisible by another atom > 1)
                bool is_atom = true;
                for (ll a : atoms) {
                    if (a > 1 && m % a == 0) { is_atom = false; break; }
                }
                if (is_atom) {
                    atoms.push_back(m);
                    S_set.insert(m);
                }
            }
        }
        
        // From atoms, generate all combinations ≤ MAX_N
        // Use priority queue or BFS
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        for (ll a : atoms) pq.push(a);
        
        while (!pq.empty()) {
            ll cur = pq.top(); pq.pop();
            for (ll a : atoms) {
                ll nxt = cur;
                // Only multiply if no square factor from same atom
                // Check if a divides nxt already
                if (nxt % a != 0) {
                    // Check limiting exponent
                    ll tmp = nxt * a;
                    if (tmp > MAX_N) break;
                    if (tmp <= MAX_N && !S_set.count(tmp)) {
                        // Verify tmp is in S
                        if (in_S(tmp, test_primes)) {
                            S_set.insert(tmp);
                            pq.push(tmp);
                        }
                    }
                } else if (a > 1 && (nxt / a) % a != 0) {
                    // One more power of a
                    ll tmp = nxt * a;
                    if (tmp > MAX_N) break;
                    if (tmp <= MAX_N && !S_set.count(tmp)) {
                        if (in_S(tmp, test_primes)) {
                            S_set.insert(tmp);
                            pq.push(tmp);
                        }
                    }
                }
            }
        }
        
        // Sum all S elements ≤ MAX_N
        ll ans = 0;
        for (ll x : S_set) {
            if (x <= MAX_N) ans += x;
        }
        cout << ans << "\n";
        return 0;
    }

    if (query == "verify") {
        cout << "PE 927: Prime-ary Tree / 素数多叉树\n\n";
        cout << "t_k(0)=1, t_k(n+1)=1+t_k(n)^k\n";
        cout << "S = intersection over primes p of {m: m|t_p(n) for some n}\n\n";
        
        // Verify known values
        vector<int> test_p = {2,3,5,7,11,13};
        cout << "Elements of S up to 20:\n";
        ll sum = 0;
        for (int m = 1; m <= 20; m++) {
            if (in_S(m, test_p)) {
                cout << "  " << m << "\n";
                sum += m;
            }
        }
        cout << "Sum = " << sum << " (expected 18)\n\n";
        
        cout << "R(1000) expected: 2089\n";
        cout << "R(10^7): compute via atomic decomposition\n";
        return 0;
    }

    cout << "PE 927: Prime-ary Tree / 素数多叉树\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
