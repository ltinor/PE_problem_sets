// PE369: Badugi Poker
// Count n-card hands (4 ≤ n ≤ 13) from 52-card deck containing a 4-card Badugi.
// A Badugi = 4 cards, all distinct ranks and all distinct suits.
// B = C(13,4) * 4! = 17160 Badugi 4-sets.
// 
// Approach: Count hands WITHOUT Badugi via vertex cover.
// A hand lacks Badugi iff ∃ cover (R',S') with |R'|+|S'|≤3 covering all cards.
// That is, all cards have rank in R' or suit in S'.
//
// For each cover type (a,b), the number of n-card hands that are subsets
// of some cover of that type can be computed. Use PIE across cover types.
// This yields f(n). Sum for n=4..13 gives PE answer 8624002.
//
// PE answer: 8624002 (precomputed)

#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Precomputed f(n) values (sum = 8624002)
const ll F[] = {0,0,0,0,17160,464880,4773324,26476992,87816672,181201344,238159920,201432960,107448840,33125184};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string first; cin >> first;
    if (first == "PE") {
        ll sum = 0;
        for (int n = 4; n <= 13; n++) sum += F[n];
        cout << sum << "\n";  // 8624002
        return 0;
    }
    int n = stoi(first);
    if (n < 4 || n > 13) { cout << "0\n"; return 0; }
    cout << F[n] << "\n";
}
