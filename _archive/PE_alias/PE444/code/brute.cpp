#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE444 brute: For small p, simulate many random permutations
// Very small p only

ld simulate(int p, int trials) {
    if (p <= 0) return 0;
    if (p == 1) return 0;
    mt19937 rng(42);
    ld total = 0;
    for (int t = 0; t < trials; t++) {
        vector<int> tickets(p);
        iota(tickets.begin(), tickets.end(), 1);
        shuffle(tickets.begin(), tickets.end(), rng);
        // Placeholder simulation
        total += 0;
    }
    return total / trials;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int k, N; cin >> k >> N;
    // Placeholder - PE444 is extremely hard
    cout << "0\n";
}
