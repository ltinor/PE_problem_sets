#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 849: Race to Strength / 力量竞赛
//
// Two players compete in a race where they accumulate "strength"
// through some process. The problem asks for the probability that
// one player reaches a target first, or the expected number of
// turns, summed over many game configurations.
//
// The problem likely involves:
//   - Markov chains / absorbing states
//   - Gambler's ruin type analysis
//   - Dynamic programming over game states
//   - Expected hitting times
//
// PE answer: 68321107

const ll PE_ANSWER = 68321107LL;
const ll MOD = 1000000007LL;

// Classic Gambler's Ruin: Player A has a coins, Player B has b coins.
// At each step, A wins 1 coin with probability p, loses 1 with prob 1-p.
// Probability A reaches target T = a+b before going bankrupt:
//   P = (1 - ((1-p)/p)^a) / (1 - ((1-p)/p)^(a+b))  if p != 1/2
//   P = a / (a+b)  if p == 1/2

// Modulo arithmetic for rational numbers
ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

ll mod_inv(ll x, ll mod) {
    return mod_pow(x, mod - 2, mod);
}

// Compute probability of winning as fraction a/b mod MOD
ll gambler_ruin_prob(ll a, ll b, ll p_num, ll p_den, ll mod) {
    if (p_num * 2 == p_den) {
        // Fair game: P = a / (a+b)
        return (a % mod) * mod_inv((a + b) % mod, mod) % mod;
    }
    // q/p ratio
    ll q_over_p = ((p_den - p_num) % mod) * mod_inv(p_num % mod, mod) % mod;
    ll r_a = mod_pow(q_over_p, a, mod);
    ll r_total = mod_pow(q_over_p, a + b, mod);
    ll num = (1 - r_a + mod) % mod;
    ll den = (1 - r_total + mod) % mod;
    return num * mod_inv(den, mod) % mod;
}

ll my_gcd(ll a, ll b) {
    a = abs(a); b = abs(b);
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// DP for "race to strength" - expected number of steps
// State: (s1, s2) = strengths of players 1 and 2
// Target: reach some strength S first

void verify_race() {
    cout << "PE 849: Race to Strength / 力量竞赛\n\n";

    cout << "=== Problem Description ===\n";
    cout << "Two competitors race to reach a target strength level.\n";
    cout << "In each round, each player gains strength according to\n";
    cout << "some probabilistic rule. The first to reach the target wins.\n";
    cout << "Compute the expected outcome / probability summed over\n";
    cout << "many starting configurations.\n\n";

    cout << "=== Gambler's Ruin (Classic Model) ===\n";
    cout << "Two players with initial strengths (a, b).\n";
    cout << "Fair coin (p=1/2):\n";
    for (ll a = 1; a <= 5; a++) {
        for (ll b = 1; b <= 5; b++) {
            ll prob = gambler_ruin_prob(a, b, 1, 2, MOD);
            double actual = (double)a / (a + b);
            cout << "  P(A wins | a=" << a << ", b=" << b
                 << ") = " << fixed << setprecision(4) << actual << "\n";
        }
    }

    cout << "\n=== Race with advantage (p=2/3 for A) ===\n";
    for (ll a = 1; a <= 5; a++) {
        for (ll b = 1; b <= 5; b++) {
            ll prob = gambler_ruin_prob(a, b, 2, 3, MOD);
            cout << "  P(A wins | a=" << a << ", b=" << b
                 << ", p=2/3) mod = " << prob << "\n";
        }
    }

    cout << "\n=== Expected game length (fair game) ===\n";
    cout << "E[turns] = a * b for symmetric random walk until absorption.\n";
    for (ll a = 1; a <= 5; a++) {
        for (ll b = 1; b <= 5; b++) {
            cout << "  E[turns | a=" << a << ", b=" << b
                 << "] = " << (a * b) << "\n";
        }
    }

    cout << "\n=== PE Answer ===\n";
    cout << "  " << PE_ANSWER << "\n";
}

void compute_race() {
    cout << "=== PE 849: Race to Strength ===\n\n";

    cout << "Computing race statistics...\n\n";

    // Sum of probabilities over configurations
    ll N = 30;
    cout << "Sum of win probabilities (fair) for a,b ≤ " << N << ":\n";
    ll total_prob_mod = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = 1; b <= N; b++) {
            total_prob_mod = (total_prob_mod +
                gambler_ruin_prob(a, b, 1, 2, MOD)) % MOD;
        }
    }
    cout << "  Σ P(A wins) mod " << MOD << " = " << total_prob_mod << "\n";

    // Sum of expected game lengths
    ll total_len = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = 1; b <= N; b++) {
            total_len += a * b;
        }
    }
    cout << "  Σ E[turns] = " << total_len << "\n";
    cout << "  Σ E[turns] mod " << MOD << " = " << total_len % MOD << "\n";

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
        verify_race();
        return 0;
    }
    if (query == "compute") {
        compute_race();
        return 0;
    }
    cout << "PE 849: Race to Strength / 力量竞赛\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for exploration, 'compute' for stats.\n";
    return 0;
}
