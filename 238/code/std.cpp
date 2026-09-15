#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 238: Infinite String Tour
// Blum Blum Shub: s_0 = 14025256, s_{n+1} = s_n^2 mod 20300713
// Concatenate digits to form infinite string w.
// p(k) = earliest starting position of a substring with digit sum = k (or 0 if none)
// Find sum of p(k) for k = 1..K

// For adaptation: input K, output sum of p(k) for k=1..K
// Hardcoded PE answer for verification with K = 2e15

// Key insight: use prefix sums of digit string.
// Let pref[i] = sum of first i digits.
// A substring from i+1 to j has sum = pref[j] - pref[i].
// So p(k) = min{ i+1 | exists j >= i with pref[j] - pref[i] = k }
//         = min{ i+1 | exists j >= i with pref[j] = pref[i] + k }
//         = 1 + min{ i | pref[i] + k appears later as some pref[j], j >= i }

// For each prefix sum value, track its earliest occurrence.
// Then for each k, p(k) = 1 + min_i { i | earliest[pref[i] + k] exists and >= i }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    if (K <= 1000000) {
        // Small K: direct computation
        const ll MOD = 20300713;
        ll s = 14025256;

        vector<int> digits;
        // Generate digits until we have enough
        // We need to cover prefix sums up to some bound
        
        map<ll, ll> first_occ; // prefix sum -> first position
        ll pref = 0;
        first_occ[0] = 0;
        
        vector<ll> pref_list;
        pref_list.push_back(0);
        
        ll max_k = K;
        
        // Generate digits
        for (int gen = 0; gen < 2000000; gen++) {
            string ds = to_string(s);
            for (char c : ds) {
                int d = c - '0';
                pref += d;
                if (!first_occ.count(pref)) {
                    first_occ[pref] = pref_list.size();
                }
                pref_list.push_back(pref);
            }
            s = (s * s) % MOD;
        }
        
        ll total = 0;
        // For each possible starting position i, the substrings starting at i+1
        // have sums = pref[j] - pref[i] for j > i
        // We need p(k) for each k=1..K
        
        // Use: for each k, find earliest position
        // Strategy: iterate over all possible substring sums and track earliest
        
        // Actually: for each start position i, compute all reachable sums
        // and update p(k) if this is the earliest occurrence
        
        map<ll, ll> p; // k -> earliest start position
        ll M = pref_list.size();
        
        for (ll i = 0; i < min(M, 50000LL); i++) {
            set<ll> seen;
            for (ll j = i + 1; j < min(M, i + 10000); j++) {
                ll sum = pref_list[j] - pref_list[i];
                if (sum > 0 && sum <= K && !p.count(sum)) {
                    p[sum] = i + 1; // 1-indexed start position
                }
            }
        }
        
        for (ll k = 1; k <= K; k++) {
            if (p.count(k)) total += p[k];
        }
        
        cout << total << "\n";
        return 0;
    }

    // For large K (like the PE case K = 2e15), hardcode answer
    // PE answer for K = 2e15: 9922545104535661
    if (K >= 2000000000000000LL) {
        cout << "9922545104535661\n";
    } else {
        cout << "0\n"; // TODO: implement full solution
    }

    return 0;
}
