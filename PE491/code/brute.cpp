#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE491: enumerate all valid arrangements for small cases
// For N ≤ 6, we can brute force all permutations

int main() {
    string query;
    getline(cin, query);
    int N = 20;
    if (!query.empty() && all_of(query.begin(), query.end(), ::isdigit)) {
        N = stoi(query);
    }
    
    if (N > 6) {
        // Too large for brute force, rely on std
        cout << "0\n";
        return 0;
    }
    
    int P = N / 2;  // number of digit pairs (digits 0..P-1 each twice)
    // Build the multiset
    vector<int> digits;
    for (int d = 0; d < P; d++) {
        digits.push_back(d);
        digits.push_back(d);
    }
    sort(digits.begin(), digits.end());
    
    ll ans = 0;
    do {
        if (digits[0] == 0) continue;  // first digit can't be 0
        // Check divisibility by 11
        int alt_sum = 0;
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) alt_sum += digits[i];
            else alt_sum -= digits[i];
        }
        if (alt_sum % 11 == 0) ans++;
    } while (next_permutation(digits.begin(), digits.end()));
    
    cout << ans << "\n";
}
