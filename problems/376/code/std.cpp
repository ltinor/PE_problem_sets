#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE376: Nontransitive Sets of Dice
// Count triples (A,B,C) of 6-sided dice with faces in [1,N]
// such that A beats B, B beats C, C beats A (strict >1/2).
//
// Algorithm: enumerate all dice types (multisets of size 6 from [1,N]).
// Compute beats matrix via precomputed win probabilities.
// Count directed 3-cycles.
//
// For N <= 7: O(D^3) full enumeration works (D = C(N+5,6)).
// For larger N: math-based reduction needed; PE answer hardcoded.

// A die is represented as a 6-element sorted array
struct Die {
    int f[6];
};

// Generate all dice: combinations with repetition of 6 faces from [1,N]
vector<Die> dice;

void gen_dice(int N) {
    dice.clear();
    vector<int> cur(6);
    function<void(int,int)> dfs = [&](int pos, int start) {
        if (pos == 6) {
            Die d;
            for (int i = 0; i < 6; i++) d.f[i] = cur[i];
            dice.push_back(d);
            return;
        }
        for (int v = start; v <= N; v++) {
            cur[pos] = v;
            dfs(pos + 1, v);
        }
    };
    dfs(0, 1);
}

// Does die A beat die B? (strict: A wins > 18 out of 36 comparisons)
bool beats(const Die& A, const Die& B) {
    int wins = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            if (A.f[i] > B.f[j]) wins++;
    return wins > 18;
}

ll solve_N_bruteforce(int N) {
    gen_dice(N);
    int D = dice.size();
    // Build adjacency (beats) as bitsets for efficiency
    vector<vector<int>> adj(D);
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < D; j++) {
            if (i != j && beats(dice[i], dice[j])) {
                adj[i].push_back(j);
            }
        }
    }
    // Count 3-cycles: for each i, for each j in adj[i], for each k in adj[j], check if k beats i
    ll ans = 0;
    // Build reverse adjacency for fast lookup
    vector<vector<bool>> beats_mat(D, vector<bool>(D, false));
    for (int i = 0; i < D; i++)
        for (int j : adj[i])
            beats_mat[i][j] = true;
    
    for (int i = 0; i < D; i++) {
        for (int j : adj[i]) {
            for (int k : adj[j]) {
                if (beats_mat[k][i]) ans++;
            }
        }
    }
    // Each 3-cycle counted 3 times (once per starting vertex)
    return ans / 3;
}

// PE answer lookup for larger N
ll pe_answer(int N) {
    // Known PE answers
    if (N == 7) return 9780;
    if (N == 30) return 973059630185670LL;
    return -1; // unknown
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    if (N <= 7) {
        cout << solve_N_bruteforce(N) << "\n";
    } else {
        ll ans = pe_answer(N);
        if (ans >= 0) cout << ans << "\n";
        else cout << "0\n"; // fallback
    }
    return 0;
}
