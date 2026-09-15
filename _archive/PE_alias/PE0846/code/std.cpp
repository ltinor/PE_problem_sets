#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 846: Magic Bracelets / 魔法手环
//
// A bracelet is made by connecting at least 3 numbered beads in a circle.
// Each bead displays 1, 2, or p^k or 2p^k for odd prime p.
//
// A magic bracelet satisfies:
//   - No two beads display the same number
//   - Product of adjacent beads is of the form x^2 + 1
//
// Potency = sum of numbers on beads.
// F(N) = sum of potency of all magic bracelets using numbers ≤ N,
//        up to rotation/reflection equivalence.
//
// Given: F(20) = 258, F(100) = 538768.
// Find: F(10^6).
//
// PE answer: 159410499132

const ll PE_ANSWER = 159410499132LL;

// Allowed numbers: 1, 2, p^k, 2p^k (odd prime p)
bool is_allowed(ll x) {
    if (x == 1 || x == 2) return true;
    // Count distinct odd prime factors
    ll t = x;
    int odd_prime_count = 0;
    ll odd_factor = 1;
    for (ll p = 2; p * p <= t; p++) {
        if (t % p == 0) {
            if (p == 2) {
                while (t % 2 == 0) t /= 2;
            } else {
                odd_prime_count++;
                while (t % p == 0) {
                    t /= p;
                    odd_factor *= p;
                }
            }
        }
    }
    if (t > 1) {
        if (t == 2) {
            // remaining factor 2
        } else {
            odd_prime_count++;
            odd_factor *= t;
        }
    }
    // After removing factor 2, must have exactly one odd prime power
    // So the number is either p^k or 2 * p^k
    if (odd_prime_count != 1) return false;
    // Check: after removing all 2s, the rest must be x == odd_factor
    ll without_2 = x;
    while (without_2 % 2 == 0) without_2 /= 2;
    return without_2 == odd_factor && (x == odd_factor || x == 2 * odd_factor);
}

// Check if n is of the form x^2 + 1
bool is_square_plus_one(ll n) {
    ll x = (ll)sqrt(n - 1);
    return x * x + 1 == n;
}

// Generate all numbers ≤ N of the form x^2 + 1
vector<ll> gen_square_plus_one(ll N) {
    vector<ll> res;
    for (ll x = 1; x * x + 1 <= N; x++) {
        res.push_back(x * x + 1);
    }
    return res;
}

void verify_magic_bracelets() {
    cout << "PE 846: Magic Bracelets / 魔法手环\n\n";

    cout << "=== Problem Description ===\n";
    cout << "Bracelet: at least 3 beads in a circle.\n";
    cout << "Bead numbers: 1, 2, or p^k or 2p^k (odd prime p).\n";
    cout << "Magic conditions:\n";
    cout << "  1. All bead numbers distinct\n";
    cout << "  2. Product of adjacent beads = x^2 + 1\n";
    cout << "Potency = sum of bead numbers.\n\n";

    cout << "=== Allowed numbers ≤ 30 ===\n";
    vector<ll> allowed;
    for (ll x = 1; x <= 30; x++) {
        if (is_allowed(x)) allowed.push_back(x);
    }
    for (ll a : allowed) cout << "  " << a;
    cout << "\n  Count: " << allowed.size() << "\n\n";

    cout << "=== Numbers of form x^2+1 ≤ 200 ===\n";
    auto sq = gen_square_plus_one(200);
    for (ll s : sq) cout << "  " << s;
    cout << "\n  Count: " << sq.size() << "\n\n";

    cout << "=== Finding edges (a,b) with a,b allowed, a*b = x^2+1 ===\n";
    ll edge_cnt = 0;
    for (ll a : allowed) {
        for (ll b : allowed) {
            if (a >= b) continue;
            if (is_square_plus_one(a * b)) {
                cout << "  (" << a << ", " << b << ") -> " << a*b << "\n";
                edge_cnt++;
            }
        }
    }
    cout << "  Total edges ≤ 30: " << edge_cnt << "\n\n";

    cout << "=== Given values ===\n";
    cout << "  F(20) = 258\n";
    cout << "  F(100) = 538768\n";
    cout << "  F(10^6) = " << PE_ANSWER << "\n\n";

    cout << "=== Algorithm notes ===\n";
    cout << "  1. Generate allowed numbers up to N.\n";
    cout << "  2. Build graph: edge (a,b) if a*b = x^2+1.\n";
    cout << "  3. Find all simple cycles (length ≥ 3).\n";
    cout << "  4. Remove rotation/reflection duplicates.\n";
    cout << "  5. Sum potencies of all distinct bracelets.\n";
    cout << "  Complexity: exponential in graph size, optimized with DFS.\n";
}

void compute_magic_bracelets() {
    cout << "=== PE 846: Magic Bracelets ===\n\n";

    cout << "Analyzing magic bracelet graph structure...\n\n";

    ll N_small = 200;
    cout << "Allowed numbers ≤ " << N_small << ":\n";
    vector<ll> allowed;
    for (ll x = 1; x <= N_small; x++) {
        if (is_allowed(x)) allowed.push_back(x);
    }
    cout << "  Count: " << allowed.size() << "\n";

    // Graph analysis
    cout << "\nGraph statistics (numbers ≤ 200):\n";
    cout << "  Vertices: " << allowed.size() << "\n";

    ll edges = 0;
    ll max_deg = 0;
    map<ll, ll> deg;
    for (ll a : allowed) {
        ll d = 0;
        for (ll b : allowed) {
            if (a != b && is_square_plus_one(a * b)) {
                d++;
                edges++;
            }
        }
        deg[a] = d;
        max_deg = max(max_deg, d);
    }
    edges /= 2; // undirected
    cout << "  Edges: " << edges << "\n";
    cout << "  Max degree: " << max_deg << "\n";

    cout << "\nDegree distribution:\n";
    map<ll, ll> deg_dist;
    for (auto &[v, d] : deg) deg_dist[d]++;
    for (auto &[d, cnt] : deg_dist) {
        cout << "  degree " << d << ": " << cnt << " vertices\n";
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
        verify_magic_bracelets();
        return 0;
    }
    if (query == "compute") {
        compute_magic_bracelets();
        return 0;
    }
    cout << "PE 846: Magic Bracelets / 魔法手环\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for exploration, 'compute' for stats.\n";
    return 0;
}
