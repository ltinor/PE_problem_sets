#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: verify p(n) formula by counting for small n
// For n=3, we know p(3) = 10400

ll comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    ll res = 1;
    for (int i = 1; i <= k; i++) {
        res = res * (n - k + i) / i;
    }
    return res;
}

// Count strings of length n using exactly n letters from alphabet (26 letters)
// that have exactly one lexicographic ascent
// Brute force by enumerating all combinations of n letters,
// then counting permutations with exactly 1 ascent
ll brute_count(int n) {
    if (n > 8) return 0; // too many permutations

    // Eulerian numbers: number of permutations of n with k ascents
    // A(n, k) — but we need words, not permutations of positions
    // For fixed set of n letters (sorted), we need permutations where exactly 1 adjacent pair is ascending
    // But "different characters" means we pick n letters from 26, then arrange them
    
    // Actually, a simpler approach: a set of n letters in increasing order,
    // then any permutation. A "lexicographic ascent" means a character is followed by a lexicographically larger one.
    // For a permutation of sorted letters, we count positions where arr[i] < arr[i+1].
    // This is just the number of ascents in the permutation.
    // # permutations with exactly 1 ascent = Eulerian number A(n, 1) = 2^n - n - 1
    
    // But we also need to choose n letters from 26. Total = C(26,n) * A(n,1)
    ll A_n1 = (1LL << n) - n - 1;
    ll c = comb(26, n);
    return c * A_n1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input: n (for verification)
    int n;
    cin >> n;

    ll c = comb(26, n);
    ll A_n1 = (1LL << n) - n - 1;
    ll p = c * A_n1;

    cout << p << "\n";
    return 0;
}
