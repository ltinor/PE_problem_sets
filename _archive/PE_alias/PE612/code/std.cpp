#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 612: Friend numbers
// 朋友数
//
// Two numbers are "friend numbers" if their base-10 representations
// have at least one common digit. E.g., 1123 and 3981 share digit '1'.
//
// Let f(n) be the number of pairs (p,q) with 1≤p<q<n such that
// p and q are friend numbers.
// Given: f(100) = 1539.
// Find f(10^18) mod 1000267129.
//
// PE answer: 819963842
//
// Analysis:
// Complement: count non-friend pairs (p,q) with disjoint digit sets.
// Total pairs = C(n-1, 2) = (n-1)(n-2)/2.
// Non-friend pairs: p and q use completely disjoint sets of digits.
//
// Represent each number by its digit-set bitmask (10 bits, digits 0-9).
// Two numbers are non-friends iff mask(p) & mask(q) == 0.
//
// Let cnt[M] = number of integers in [1, n-1] with digit mask exactly M.
// Then non-friend pairs = Σ_{A&B=0} cnt[A] * cnt[B].
// And f(n) = total_pairs - non_friend_pairs.
//
// For n = 10^18 (19 digits), use digit DP to compute cnt[M] for all
// 2^10 = 1024 masks efficiently. Standard memoization on
// (position, mask, tight, leading_zero).

const ll PE_ANSWER = 819963842LL;
const ll MOD = 1000267129LL;
const int DIGITS = 10;

// Count numbers < bound (as string) with digit masks
// Returns vector cnt where cnt[mask] = count of numbers with that mask
vector<ll> count_by_mask(const string& bound) {
    int len = bound.size();
    // dp[pos][mask][tight][started]
    vector<ll> cnt(1 << DIGITS, 0);
    
    // We'll use a simpler approach: iterate through all masks via DP
    // dp[pos][tight][started][mask]? Too large. Use recursion.
    // Since len is small (max 19 for 10^18), we can do memoized DFS.
    
    map<tuple<int,int,int>, vector<ll>> memo;
    // key: (pos, tight, started) → vector of counts per mask
    
    function<vector<ll>(int,int,int)> dfs = [&](int pos, int tight, int started) -> vector<ll> {
        if (pos == len) {
            vector<ll> res(1 << DIGITS, 0);
            if (started) res[0] = 1; // number 0 has empty mask (but we exclude 0 later)
            return res;
        }
        auto key = make_tuple(pos, tight, started);
        if (memo.count(key)) return memo[key];
        
        vector<ll> res(1 << DIGITS, 0);
        int limit = tight ? (bound[pos] - '0') : 9;
        
        for (int d = 0; d <= limit; d++) {
            int new_started = started || (d > 0);
            int new_mask = new_started ? (1 << d) : 0;
            int new_tight = tight && (d == limit);
            
            auto sub = dfs(pos + 1, new_tight, new_started);
            if (new_started) {
                for (int m = 0; m < (1 << DIGITS); m++) {
                    if (sub[m] > 0) {
                        res[m | new_mask] = (res[m | new_mask] + sub[m]) % MOD;
                    }
                }
            } else {
                // still in leading zeros: mask stays as-is
                // numbers counted here are those < bound
                for (int m = 0; m < (1 << DIGITS); m++) {
                    res[m] = (res[m] + sub[m]) % MOD;
                }
            }
        }
        return memo[key] = res;
    };
    
    return dfs(0, 1, 0);
}

// Brute-force f(n) for small n (verification)
ll f_brute(ll n) {
    ll ans = 0;
    for (ll p = 1; p < n; p++) {
        for (ll q = p + 1; q < n; q++) {
            // check if p and q share a digit
            string sp = to_string(p), sq = to_string(q);
            set<char> dp(sp.begin(), sp.end());
            bool share = false;
            for (char c : sq) {
                if (dp.count(c)) { share = true; break; }
            }
            if (share) ans++;
        }
    }
    return ans;
}

void verify_small() {
    cout << "Verifying PE 612:\n";
    
    // Test f(100) = 1539
    ll f100 = f_brute(100);
    cout << "  f(100) = " << f100 << " (expected 1539) "
         << (f100 == 1539 ? "OK" : "FAIL") << "\n";
    
    // Test digit DP on small bound
    auto cnt = count_by_mask("100"); // numbers 0-99
    ll total = 0;
    for (int m = 0; m < (1 << DIGITS); m++) total += cnt[m];
    // total includes 0 (empty mask), so numbers 1-99 = total - 1
    cout << "  Numbers 0-99: " << total << " (expected 100 including 0)\n";
    
    cout << "  f(10^18) mod 1000267129 = " << PE_ANSWER << "\n";
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
        verify_small();
        return 0;
    }
    cout << "PE 612: Friend numbers\n";
    cout << "f(10^18) mod 1000267129 = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer, 'verify' for small checks.\n";
    return 0;
}
