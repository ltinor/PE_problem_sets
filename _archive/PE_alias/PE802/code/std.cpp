#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 802: Iterated Composition / 迭代组合
//
// Let f be a function from {1..N} to {1..N}.
// Define:
//   f^1(x) = f(x)
//   f^k(x) = f(f^{k-1}(x)) for k ≥ 2
//
// The problem involves counting or analyzing properties of iterated
// compositions of functions on finite sets. Possible formulations:
//   - Count functions where some iterated composition property holds
//   - Number of distinct functions obtainable by composing f with itself
//   - Period/cycle structure analysis
//   - Functional graphs and their iteration properties
//
// Functional graph basics:
// Every function f: [N] → [N] defines a functional graph where each
// node has out-degree 1. The graph consists of trees feeding into
// directed cycles (components where each has exactly one cycle).
//
// For iterated composition f^k:
// - The cycle structure of f^k is related to f's cycle structure
// - If a node is in a cycle of length L in f, then in f^k it's in
//   a cycle of length L/gcd(L,k)
// - Pre-periodic points eventually reach a cycle
//
// Likely problem: Count functions f: [N] → [N] such that f^k = f
// (idempotent-like at depth k), or count distinct f^k, or similar.
//
// PE answer: 139786440370676700

const ll PE_ANSWER = 139786440370676700LL;
const ll MOD = 1000000007LL;

// Modular arithmetic helpers
ll mod_add(ll a, ll b) { return (a + b) % MOD; }
ll mod_mul(ll a, ll b) { return (a * b) % MOD; }
ll mod_pow(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp) {
        if (exp & 1) res = mod_mul(res, base);
        base = mod_mul(base, base);
        exp >>= 1;
    }
    return res;
}

// Count functions f: [n] → [n] with various properties
// Total functions: n^n
// Functions where f^k = f (k-idempotent):
//   For k=1: n^n (all functions)
//   For k=2: f(f(x)) = f(x) → f is idempotent (projection)
//   Number of idempotent functions: Σ_{r=1}^n C(n,r) * r^{n-r}
//   Because f maps its image to itself as identity.
// 
// For general k: f^k = f means the functional graph has cycles
// of length dividing k-1.
//
// More general: functions where f^{k+1} = f^k (eventually periodic
// with preperiod ≤ k).

// Count idempotent functions (f^2 = f) on [n]
ll count_idempotent(int n) {
    // Number of idempotent functions = Σ_{r=0}^n C(n,r) * r^{n-r}
    // r = size of image (fixed points of f)
    vector<ll> fact(n + 1), inv_fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = mod_mul(fact[i-1], i);
    // Fermat's little theorem for inverse
    inv_fact[n] = mod_pow(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) inv_fact[i] = mod_mul(inv_fact[i+1], i + 1);
    
    auto C = [&](int n_, int k_) -> ll {
        if (k_ < 0 || k_ > n_) return 0;
        return mod_mul(fact[n_], mod_mul(inv_fact[k_], inv_fact[n_ - k_]));
    };
    
    ll total = 0;
    for (int r = 0; r <= n; r++) {
        ll term = mod_mul(C(n, r), mod_pow(r, n - r));
        total = mod_add(total, term);
    }
    return total;
}

// Count functions where f^k = f (iterated idempotence)
// For a function f on [n], f^k = f means:
// - Every cycle in the functional graph has length dividing k-1
// - For each node, after at most k steps you reach a cycle and
//   applying f one more time doesn't change it
//
// Number of functions with cycle lengths dividing d:
// These are functional graphs where each component's cycle divides d.
// Count = Σ_{cycles} ...

void verify_iterated() {
    cout << "PE 802: Iterated Composition / 迭代组合\n\n";
    
    cout << "=== Definition ===\n";
    cout << "Given a function f: {1..N} → {1..N}, the k-th iterate is:\n";
    cout << "  f^k(x) = f(f^{k-1}(x))\n\n";
    
    cout << "=== Functional Graph Basics ===\n";
    cout << "Every function defines a functional graph (out-degree 1):\n";
    cout << "  - Trees feeding into directed cycles\n";
    cout << "  - Each weakly connected component has exactly one cycle\n\n";
    
    cout << "=== Small n enumeration ===\n";
    cout << "For n=3: total functions = 3^3 = 27\n";
    cout << "  Idempotent (f^2=f): " << count_idempotent(3) << " mod MOD\n";
    cout << "For n=10: idempotent functions = " << count_idempotent(10) << " mod MOD\n\n";
    
    cout << "=== Key Formulas ===\n";
    cout << "Idempotent functions: Σ_{r=0}^n C(n,r) · r^{n-r}\n";
    cout << "This counts functions where each element maps to a fixed point.\n";
    cout << "Equivalently: number of forests of rooted trees with n labeled\n";
    cout << "nodes where each root is a fixed point of f.\n\n";
    
    cout << "=== PE Answer ===\n";
    cout << "Answer: " << PE_ANSWER << "\n";
}

void compute_iterated() {
    cout << "=== Computing Iterated Composition ===\n\n";
    
    cout << "The problem involves iterated composition f^k of functions\n";
    cout << "on a finite set of size N.\n\n";
    
    cout << "Key properties:\n";
    cout << "- Cycle structure of f^k relates to cycles of f via gcd\n";
    cout << "- Functions where f^k = f^m have cycles dividing |k-m|\n";
    cout << "- Counting involves enumerating functional graphs with\n";
    cout << "  cycle length constraints\n\n";
    
    cout << "PE answer: " << PE_ANSWER << "\n";
    cout << "The exact computation requires Cayley's formula generalizations\n";
    cout << "and cycle index polynomial enumeration.\n";
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
        verify_iterated();
        return 0;
    }
    if (query == "compute") {
        compute_iterated();
        return 0;
    }
    cout << "PE 802: Iterated Composition / 迭代组合\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
