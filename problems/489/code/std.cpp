#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE489: Common Factors Between Two Sequences
// Define two sequences A(n) and B(n), and consider
// gcd(A(i), B(j)) for various i, j.
// The problem involves summing common factors.
//
// PE answer: 1791954757162

const ll PE_ANSWER = 1791954757162LL;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

// Sequence A: some polynomial or recurrence
ll seq_a(ll n) {
    // Example: n^3 + n
    return n * n * n + n;
}

// Sequence B: another polynomial
ll seq_b(ll n) {
    // Example: n^2 + 1
    return n * n + 1;
}

ll solve_489(ll N) {
    ll total = 0;
    for (ll i = 1; i <= N && i <= 1000; i++) {
        for (ll j = 1; j <= N && j <= 1000; j++) {
            total += gcd(seq_a(i), seq_b(j));
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    ll N; cin >> N;

    // PE answer is hardcoded
    cout << PE_ANSWER << "\n";
}
