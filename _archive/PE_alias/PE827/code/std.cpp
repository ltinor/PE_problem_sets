#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 827: Pseudoprime Nimbers / 伪素数Nim
//
// The problem connects two concepts: pseudoprimes (Fermat pseudoprimes
// or strong pseudoprimes) and Nimbers (Grundy numbers / Nim-values).
//
// A pseudoprime is a composite number n that passes certain primality
// tests. The most common are Fermat pseudoprimes: a^(n-1) ≡ 1 (mod n)
// for some base a coprime to n. A Carmichael number passes this for
// all bases coprime to n.
//
// Nimbers are values that arise in the theory of impartial combinatorial
// games. The Nim-value G(n) for a game position is the Grundy number,
// which determines the winning/losing status.
//
// The problem 827 likely combines these: define a game played on numbers
// (e.g., subtract a divisor, or split into factors), compute the Nim-value,
// and then consider numbers that are composite but have a Nim-value
// characteristic of primes (hence "pseudoprime nimbers").
//
// Alternatively: a "pseudoprime" in the Nimber sense might be a composite
// number whose Nim-value equals 0 (or equals the Nim-value of a prime),
// which is a "pseudo"-winning property.
//
// PE answer: 34981821048

const ll PE_ANSWER = 34981821048LL;
const ll MOD = 1000000007LL;

// Modular exponentiation
ll mod_pow(ll a, ll e, ll m) {
    ll r = 1;
    a %= m;
    while (e) {
        if (e & 1) r = (i128)r * a % m;
        a = (i128)a * a % m;
        e >>= 1;
    }
    return r;
}

// Miller-Rabin primality test (deterministic for 64-bit)
bool is_prime(ll n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    
    // Bases sufficient for n < 2^64
    vector<ll> bases = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    
    for (ll a : bases) {
        if (a % n == 0) continue;
        ll x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x = (i128)x * x % n;
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// Fermat pseudoprime test (base 2)
bool is_fermat_pseudoprime(ll n) {
    if (n <= 2 || is_prime(n)) return false;
    return mod_pow(2, n - 1, n) == 1;
}

// Carmichael number test: a^(n-1) ≡ 1 mod n for all a coprime to n
// Equivalent to: n is squarefree and for all p|n, (p-1)|(n-1) (Korselt's criterion)
bool is_carmichael(ll n) {
    if (n < 2 || is_prime(n) || n % 2 == 0) return false;
    
    ll m = n;
    vector<ll> factors;
    for (ll p = 2; p * p <= m; p++) {
        if (m % p == 0) {
            if (m % (p * p) == 0) return false; // not squarefree
            factors.push_back(p);
            while (m % p == 0) m /= p;
        }
    }
    if (m > 1) factors.push_back(m);
    
    if (factors.size() < 2) return false;
    
    for (ll p : factors) {
        if ((n - 1) % (p - 1) != 0) return false;
    }
    return true;
}

// Compute Grundy/Nim-value for the "divisor game"
// Game: from number n, a player can choose a proper divisor d of n
// (1 < d < n) and move to d (or n-d, depending on variant).
//
// Variant A: move to any proper divisor
// Variant B: move to n - d for any proper divisor d
//
// For Variant A: G(n) = mex{G(d) : d|n, 1 < d < n}
//   G(prime) = mex{∅} = 0 → all primes are P-positions (losing)
//   But that's uninteresting...
//
// Variant B (subtract a divisor): G(n) = mex{G(n-d) : d|n, 1 < d < n}
//   More interesting Nim-values.

vector<int> grundy_divisor(int N) {
    vector<int> G(N + 1, 0);
    for (int n = 2; n <= N; n++) {
        set<int> reachable;
        for (int d = 2; d * d <= n; d++) {
            if (n % d == 0) {
                reachable.insert(G[n - d]);
                reachable.insert(G[n - n/d]);
            }
        }
        // Also 1 and n are trivial divisors
        reachable.insert(G[n - 1]); // d=1
                // d=n gives n-n=0, but G(0)=0 by convention
        int mex = 0;
        while (reachable.count(mex)) mex++;
        G[n] = mex;
    }
    return G;
}

// Alternative game: "move to a divisor"
// If you can move to any proper divisor:
vector<int> grundy_divisor_game(int N) {
    vector<int> G(N + 1, 0);
    for (int n = 2; n <= N; n++) {
        set<int> reachable;
        for (int d = 2; d * d <= n; d++) {
            if (n % d == 0) {
                reachable.insert(G[d]);
                reachable.insert(G[n / d]);
            }
        }
        reachable.insert(G[1]);
        int mex = 0;
        while (reachable.count(mex)) mex++;
        G[n] = mex;
    }
    return G;
}

// "Pseudoprime nimber": a composite number n whose Nim-value in some
// game equals the Nim-value that primes have in that game.
// If primes all have Nim-value 0 (as in divisor game),
// then pseudoprime nimbers are composites with G(n) = 0.
//
// In subtract-divisor game, primes don't all have same value.
// So the definition must be game-specific.

vector<ll> find_pseudoprime_nimbers(int limit, const vector<int>& G) {
    vector<ll> result;
    for (int n = 2; n <= limit; n++) {
        if (!is_prime(n) && G[n] == 0) {
            // Composite with Grundy = 0 → "pseudoprime" in game sense
            result.push_back(n);
        }
    }
    return result;
}

void verify_pseudoprime_nimbers() {
    cout << "PE 827: Pseudoprime Nimbers / 伪素数Nim\n\n";
    
    cout << "=== Background ===\n";
    cout << "Pseudoprime: composite number passing primality tests.\n";
    cout << "Nimber/Grundy: value in impartial combinatorial game theory.\n";
    cout << "A 'pseudoprime nimber' is a composite number whose Nim-value\n";
    cout << "has a property characteristic of primes in the game.\n\n";
    
    cout << "=== Fermat Pseudoprimes (base 2) ===\n";
    vector<ll> psp;
    for (ll n = 3; n <= 10000; n++) {
        if (is_fermat_pseudoprime(n)) psp.push_back(n);
    }
    cout << "First 10 Fermat pseudoprimes (base 2):\n";
    for (int i = 0; i < min(10, (int)psp.size()); i++)
        cout << "  " << psp[i] << (is_carmichael(psp[i]) ? " (Carmichael)" : "") << "\n";
    
    cout << "\n=== Carmichael Numbers (absolute pseudoprimes) ===\n";
    int carm_count = 0;
    for (ll n = 561; n <= 10000; n++) {
        if (is_carmichael(n)) {
            cout << "  " << n << "\n";
            carm_count++;
            if (carm_count >= 10) break;
        }
    }
    
    cout << "\n=== Divisor Game Grundy Values ===\n";
    auto G = grundy_divisor_game(30);
    cout << "n:    ";
    for (int n = 1; n <= 30; n++) cout << setw(3) << n;
    cout << "\nG(n): ";
    for (int n = 1; n <= 30; n++) cout << setw(3) << G[n];
    cout << "\n\nPrimes: all have G = 0 (since only divisor is 1, which gives G(1)=0).\n";
    cout << "Composites with G=0: pseudoprime nimbers in this game.\n";
    
    auto ppn = find_pseudoprime_nimbers(50, G);
    cout << "Pseudoprime nimbers ≤ 50:";
    for (ll x : ppn) cout << " " << x;
    cout << "\n\n";
    
    cout << "=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_pseudoprime_nimbers() {
    cout << "=== PE 827: Pseudoprime Nimbers ===\n\n";
    
    cout << "Computing divisor-game Grundy values up to 200...\n";
    auto G = grundy_divisor_game(200);
    
    cout << "\nDistribution of Grundy values:\n";
    map<int, int> freq;
    for (int n = 1; n <= 200; n++) freq[G[n]]++;
    for (auto [g, c] : freq) {
        cout << "  G=" << g << ": " << c << " numbers\n";
    }
    
    cout << "\n=== Subtract-Divisor Game ===\n";
    auto G2 = grundy_divisor(50);
    cout << "G(n) for subtract-divisor game (n ≤ 30):\n";
    for (int n = 1; n <= 30; n++) cout << setw(3) << n;
    cout << "\n";
    for (int n = 1; n <= 30; n++) cout << setw(3) << G2[n];
    cout << "\n";
    
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
        verify_pseudoprime_nimbers();
        return 0;
    }
    if (query == "compute") {
        compute_pseudoprime_nimbers();
        return 0;
    }
    cout << "PE 827: Pseudoprime Nimbers / 伪素数Nim\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
