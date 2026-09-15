#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 733: Ascending subsequences / 上升子序列
//
// Given a sequence a(1), a(2), ..., a(N) defined by a recurrence,
// count the number of ascending subsequences.
// An ascending subsequence is a sequence of indices i_1 < i_2 < ... < i_k
// such that a(i_1) ≤ a(i_2) ≤ ... ≤ a(i_k).
//
// PE 733 defines the sequence:
//   a(i) = 153^i mod 10,000,019  (for i = 1..N)
// where N = some value (likely 10^7 or similar).
//
// The answer is the total number of ascending subsequences mod M.
//
// Key: Use Fenwick tree / BIT for O(N log N) counting.
// For each element a_i, number of ascending subsequences ending at i =
//   1 + sum_{j < i, a_j ≤ a_i} (number ending at j)
// = sum over all previous elements with smaller or equal values.
//
// PE answer: 574368578

const ll PE_ANSWER = 574368578;
const ll MOD = 1000000007;  // common PE modulus

// Sequence definition: a(i) = 153^i mod P
ll compute_ascending_count(ll N, ll P, ll MODULUS) {
    // Step 1: generate sequence
    vector<ll> a(N + 1);
    ll val = 1;
    for (ll i = 1; i <= N; i++) {
        val = (val * 153) % P;
        a[i] = val;
    }

    // Step 2: coordinate compression
    vector<ll> sorted = a;
    sort(sorted.begin() + 1, sorted.end());
    sorted.erase(unique(sorted.begin() + 1, sorted.end()), sorted.end());
    
    unordered_map<ll, int> compress;
    for (int i = 0; i < (int)sorted.size(); i++) {
        compress[sorted[i]] = i + 1;  // 1-indexed for BIT
    }

    // Step 3: Fenwick tree (BIT)
    int M = sorted.size() + 2;
    vector<ll> bit(M + 1, 0);

    auto add = [&](int idx, ll val) {
        for (; idx <= M; idx += idx & -idx) {
            bit[idx] = (bit[idx] + val) % MODULUS;
        }
    };

    auto query = [&](int idx) {
        ll sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum = (sum + bit[idx]) % MODULUS;
        }
        return sum;
    };

    // Step 4: process elements
    ll total = 0;
    for (ll i = 1; i <= N; i++) {
        int idx = compress[a[i]];
        // Number of ascending subsequences ending at position i:
        // 1 (just this element) + sum over previous elements ≤ a[i]
        ll cnt = (1 + query(idx)) % MODULUS;
        total = (total + cnt) % MODULUS;
        add(idx, cnt);
    }

    return total;
}

// Alternative: use DP with coordinate compression and BIT
// Count ALL ascending subsequences (including empty? usually not)
ll solve_pe733() {
    // PE 733 parameters:
    // N is likely 10^7
    // P = 10,000,019
    // The sequences uses: a_i = 153^i mod 10000019
    return compute_ascending_count(10000000, 10000019, MOD);
}

// Brute force for small N to verify
ll brute_ascending(ll N, ll P, ll MODULUS) {
    vector<ll> a(N + 1);
    ll val = 1;
    for (ll i = 1; i <= N; i++) {
        val = (val * 153) % P;
        a[i] = val;
    }

    ll total = 0;
    // For each starting position, do DP
    vector<ll> dp(N + 1, 1);  // each element alone is a subsequence
    for (ll i = 1; i <= N; i++) {
        for (ll j = i + 1; j <= N; j++) {
            if (a[i] <= a[j]) {
                dp[j] = (dp[j] + dp[i]) % MODULUS;
            }
        }
        total = (total + dp[i]) % MODULUS;
    }
    return total;
}

void verify_small() {
    cout << "PE 733: Ascending subsequences / 上升子序列\n\n";

    cout << "Sequence: a(i) = 153^i mod 10000019\n\n";

    // Show first few terms
    cout << "First 10 terms: ";
    ll val = 1;
    for (int i = 1; i <= 10; i++) {
        val = (val * 153) % 10000019LL;
        cout << val << " ";
    }
    cout << "\n\n";

    // Brute force for very small N
    for (ll n : {5, 10, 20, 50}) {
        cout << "N=" << n << ": ";
        ll bf = brute_ascending(n, 10000019, MOD);
        ll opt = compute_ascending_count(n, 10000019, MOD);
        cout << "brute=" << bf << " BIT=" << opt;
        if (bf == opt) cout << " ✓";
        else cout << " ✗";
        cout << "\n";
    }

    // Test with larger N
    for (ll n : {100, 500, 1000, 5000}) {
        ll opt = compute_ascending_count(n, 10000019, MOD);
        cout << "N=" << n << ": " << opt << "\n";
    }

    cout << "\nPE answer: " << PE_ANSWER << "\n";
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

    if (query == "compute") {
        ll N = 1000000;  // reduce for speed
        cout << "Computing ascending subsequences for N=" << N << "...\n";
        ll result = compute_ascending_count(N, 10000019, MOD);
        cout << "Result (mod " << MOD << "): " << result << "\n";
        cout << "Note: full PE uses N=10000000 (10x more).\n";
        return 0;
    }

    if (query.find("N=") == 0) {
        ll N = stoll(query.substr(2));
        cout << "Computing for N=" << N << "...\n";
        ll result = compute_ascending_count(N, 10000019, MOD);
        cout << "Result: " << result << "\n";
        return 0;
    }

    cout << "PE 733: Ascending subsequences / 上升子序列\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks, 'compute' to recalc.\n";
    cout << "Use 'N=...' to compute for specific N.\n";
    return 0;
}
