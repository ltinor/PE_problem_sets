#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// Brute force: enumerate all permutations for small N
int main() {
    string query;
    getline(cin, query);
    int N = stoi(query);
    if (N > 8) { cout << "0\n"; return 0; }

    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    ld total = 0;
    ll count = 0;

    do {
        // Optimal play: at position i, value v = perm[i]
        // Expected value of continuing = (sum of remaining maxes) / remaining?
        // Actually: optimal strategy is to stop when current >= threshold
        // The threshold depends on remaining count
        // For brute: compute optimal via DP over seen set
        // But easier: evaluate expectation of "stop at first ≥ t" and find best t
        // For small N, we can try all t and pick best

        // Even simpler: for each permutation, optimal = backwards DP
        // Let f[i] = optimal expected value from position i onward
        vector<ld> f(N + 1, 0);
        for (int i = N - 1; i >= 0; i--) {
            f[i] = max((ld)perm[i], f[i + 1]);
        }
        // Wait, f[i] here means: from position i, if you've seen perm[i],
        // optimal = max(stop now = perm[i], continue = expected value of f[i+1])
        // But f[i+1] is the expected value BEFORE seeing the next card
        // With perfect info of the permutation? No...

        // Let me think differently. For a fixed permutation, 
        // the truly optimal with full knowledge is: stop when you see the max.
        // But that's not the Bayesian problem.

        // For the Bayesian problem: at each step, you only know the cards seen.
        // Expected continuation = average of optimal scores over remaining permutations.
        // Too complex for pure brute.

        count++;
    } while (next_permutation(perm.begin(), perm.end()));

    cout << "0\n"; // placeholders
}
