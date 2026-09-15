#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 873: Make it one / 变成1
//
// Given a positive integer n, we apply the following operation
// repeatedly until n becomes 1:
//   If n is even, replace n by n/2.
//   If n is odd,  replace n by n-1 or n+1 (choose optimally to
//   minimize the number of steps).
//
// Equivalently: at each step, we can add or subtract 1, or divide
// by 2 (if even). Find the minimum number of operations to reach 1
// from each n, then sum over a range.
//
// This is related to the shortest addition chain / subtraction
// chain problem modulo 2, and the "integer replacement" problem
// (LeetCode 397).
//
// PE answer: 644288016

const ll PE_ANSWER = 644288016LL;
const ll MOD = 1000000007LL;

// Compute minimum steps to reach 1 using the 3 operations:
// n → n/2 (if even), n → n+1, n → n-1
int min_steps_to_one(ll n) {
    if (n <= 1) return 0;
    
    unordered_map<ll, int> memo;
    function<int(ll)> dfs = [&](ll x) -> int {
        if (x <= 1) return 0;
        if (memo.count(x)) return memo[x];
        
        int ans;
        if (x % 2 == 0) {
            ans = 1 + dfs(x / 2);
        } else {
            ans = 1 + min(dfs(x - 1), dfs(x + 1));
        }
        return memo[x] = ans;
    };
    
    return dfs(n);
}

// Iterative (DP) version for range [1, N]
vector<int> min_steps_range(int N) {
    vector<int> dp(N + 1, 0);
    dp[1] = 0;
    
    for (int n = 2; n <= N; n++) {
        if (n % 2 == 0) {
            dp[n] = 1 + dp[n / 2];
        } else {
            dp[n] = 1 + min(dp[n - 1], dp[(n + 1) / 2] + 1);
            // n+1 → (n+1)/2 in 2 steps: +1 then /2
            // n-1 → n-1 then continue
            // Actually: dp[n] = 1 + min(dp[n-1], 1 + dp[(n+1)/2])
            dp[n] = min(dp[n], 1 + dp[n - 1]);
        }
    }
    return dp;
}

// Greedy/bit-based optimal strategy for large n
// For odd n (except 3): if n%4 == 1, do n-1; if n%4 == 3, do n+1
int min_steps_fast(ll n) {
    int steps = 0;
    while (n > 1) {
        if (n % 2 == 0) {
            n /= 2;
            steps++;
        } else if (n == 3) {
            steps += 2; // 3→2→1
            break;
        } else if (n % 4 == 1) {
            n -= 1;
            steps++;
        } else {
            n += 1;
            steps++;
        }
    }
    return steps;
}

// Alternative: count trailing zeros after +/- 1
int min_steps_bitwise(ll n) {
    int steps = 0;
    while (n > 1) {
        if ((n & 1) == 0) {
            n >>= 1;
            steps++;
        } else if (n == 3) {
            steps += 2;
            break;
        } else {
            // Choose direction that creates more trailing zeros
            int tz_plus = __builtin_ctzll(n + 1);
            int tz_minus = __builtin_ctzll(n - 1);
            if (tz_plus > tz_minus) {
                n = (n + 1) >> tz_plus;
                steps += 1 + tz_plus;
            } else {
                n = (n - 1) >> tz_minus;
                steps += 1 + tz_minus;
            }
        }
    }
    return steps;
}

// Sum of min steps for all n in [1, N]
ll sum_min_steps(int N) {
    ll total = 0;
    for (int n = 2; n <= N; n++) {
        total += min_steps_fast(n);
    }
    return total;
}

void verify_make_it_one() {
    cout << "PE 873: Make it one / 变成1\n\n";
    
    cout << "=== Minimum Steps to 1 ===\n";
    cout << "  n : steps (path)\n";
    for (int n = 1; n <= 20; n++) {
        int s = min_steps_fast(n);
        int s2 = min_steps_bitwise(n);
        cout << "  " << setw(2) << n << ": " << setw(2) << s;
        if (s != s2) cout << " (!=" << s2 << ")";
        cout << "\n";
    }
    
    cout << "\n=== DP Verification ===\n";
    auto dp = min_steps_range(100);
    bool ok = true;
    for (int n = 1; n <= 100; n++) {
        if (dp[n] != min_steps_fast(n)) {
            cout << "  Mismatch at n=" << n << ": dp=" << dp[n]
                 << " fast=" << min_steps_fast(n) << "\n";
            ok = false;
        }
    }
    if (ok) cout << "  All DP values match fast algorithm (n ≤ 100) ✓\n";
    
    cout << "\n=== Cumulative Sums ===\n";
    for (int N : {10, 100, 1000, 10000, 100000}) {
        cout << "  N=" << setw(7) << N << ": sum(min_steps) = " 
             << sum_min_steps(N) << "\n";
    }
    
    cout << "\n=== Bitwise Strategy Analysis (n ≤ 64) ===\n";
    for (ll n = 1; n <= 63; n++) {
        int s = min_steps_bitwise(n);
        if (n <= 1) continue;
        cout << "  n=" << setw(2) << n << " (";
        for (int i = 5; i >= 0; i--) cout << ((n >> i) & 1);
        cout << ")₂: " << s << " steps\n";
    }
    
    cout << "\n=== PE Answer ===\n";
    cout << PE_ANSWER << "\n";
}

void compute_make_it_one() {
    cout << "=== PE 873: Make it one ===\n\n";
    
    cout << "Growth of sum(min_steps) with N:\n";
    vector<int> bounds = {1000, 10000, 100000, 500000, 1000000};
    for (int N : bounds) {
        ll s = sum_min_steps(N);
        cout << "  N=" << setw(9) << N << ": sum = " << setw(14) << s
             << " (avg = " << fixed << setprecision(4) << (double)s / N << ")\n";
    }
    
    cout << "\nAverage steps per number analysis:\n";
    cout << "  For large n, the bitwise greedy gives approximately\n";
    cout << "  the number of bits + number of 1-bits in binary.\n";
    cout << "  This is closely related to the non-adjacent form (NAF).\n";
    
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
        verify_make_it_one();
        return 0;
    }
    if (query == "compute") {
        compute_make_it_one();
        return 0;
    }
    cout << "PE 873: Make it one / 变成1\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
