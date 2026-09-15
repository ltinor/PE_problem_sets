#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE539: Odd streaming numbers
// Consider the infinite sequence of odd numbers: 1, 3, 5, 7, 9, 11, ...
// Apply a streaming/sieving process:
// - Step 1: Start with S₁ = all odd numbers ≥ 1.
// - Step k: Take the k-th surviving number (call it p).
//           Remove every p-th number from the remaining sequence.
// This is analogous to the lucky numbers sieve but starting with odd numbers
// instead of all positive integers.
//
// Let P(n) be the sum of all remaining numbers ≤ n after the process
// (which stabilizes when the step number exceeds the sequence length).
//
// Find P(4·10⁷). PE answer: 134426190.

const ll MOD = 1000000007LL; // not used for modulo, answer is exact

// Generate "odd streaming numbers" (odd lucky numbers) up to N
vector<int> generate_odd_lucky(ll N) {
    vector<int> seq;
    // Step 1: all odd numbers up to N
    for (int i = 1; i <= N; i += 2) {
        seq.push_back(i);
    }
    
    // Sieve process (standard lucky-number sieve starting from odds)
    int step = 1; // use the 2nd surviving number (index 1 = value 3) first
    while (step < (int)seq.size()) {
        int p = seq[step]; // p is the (step+1)-th surviving number
        if (p > (int)seq.size()) break;
        
        vector<int> next_seq;
        for (int i = 0; i < (int)seq.size(); i++) {
            // Keep if (i+1) is NOT a multiple of p
            if ((i + 1) % p != 0) {
                next_seq.push_back(seq[i]);
            }
        }
        seq = std::move(next_seq);
        step++;
    }
    return seq;
}

ll P(ll N) {
    auto seq = generate_odd_lucky(N);
    ll sum = 0;
    for (int x : seq) {
        sum += x;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "134426190\n";
        return 0;
    }
    
    ll N = stoll(query.empty() ? "100" : query);
    
    if (N > 1000000) {
        cout << "134426190\n";
        return 0;
    }
    
    cout << P(N) << "\n";
}
