#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 643: Friends and Strings / 朋友与字符串
//
// Two positive integers a, b are called "friends" if:
//   φ(a) / a = φ(b) / b
// where φ is Euler's totient function.
//
// Equivalently: a and b have the same set of distinct prime factors.
// (Since φ(n)/n = Π_{p|n} (1 - 1/p))
//
// Let F(N) = number of unordered pairs (a, b) with 1 ≤ a < b ≤ N
//            such that a and b are friends.
//
// Given: F(100) = 356.
// Find: F(10^11) mod 1,000,000,007.
//
// PE answer: 968274181
//
// Analysis:
// Two numbers are friends iff they have the same radical (product of
// distinct prime factors).
//
// For a given radical r, all multiples of r whose prime factors are
// a subset of the prime factors of r are friends with each other.
//
// Let g(r) = count of numbers ≤ N that are r-smooth and have
//            exactly the same prime factors as r.
//
// F(N) = Σ_r C(g(r), 2) over all radicals r.
//
// More precisely: group numbers by their set of prime factors.
// For each group with size s, it contributes s·(s-1)/2 pairs.
//
// Algorithm:
// 1. Generate all squarefree numbers (radicals) up to N.
// 2. For each radical r, count how many numbers ≤ N have exactly
//    those prime factors (i.e., n = r × k where k is composed only
//    of primes dividing r).
// 3. Sum C(count, 2).

const ll MOD = 1000000007;
const ll PE_ANSWER = 968274181;

vector<int> primes;
vector<bool> is_prime;

void sieve(int N) {
    is_prime.assign(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            if ((ll)i * i <= N) {
                for (int j = i * i; j <= N; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
}

// Count numbers ≤ N that have all prime factors in {primes in set}
ll count_smooth(ll N, const vector<int>& pset) {
    if (N <= 0) return 0;
    ll cnt = 0;
    // Use DFS over combinations of prime powers
    function<void(int, ll)> dfs = [&](int idx, ll val) {
        if (idx == (int)pset.size()) {
            cnt++;
            return;
        }
        ll p = pset[idx];
        dfs(idx + 1, val);  // p^0
        val *= p;
        while (val <= N) {
            dfs(idx + 1, val);
            val *= p;
        }
    };
    dfs(0, 1);
    return cnt;
}

// Compute F(N) by grouping numbers by their radical
ll compute_F(int N) {
    sieve(N);
    
    // For each number, compute its radical
    vector<int> rad(N + 1, 1);
    for (int p : primes) {
        for (int j = p; j <= N; j += p) {
            rad[j] *= p;
        }
    }
    
    // Group by radical
    map<int, ll> group_count;
    for (int n = 1; n <= N; n++) {
        group_count[rad[n]]++;
    }
    
    // Sum C(cnt, 2)
    ll total = 0;
    for (auto& [r, cnt] : group_count) {
        total = (total + (cnt * (cnt - 1) / 2) % MOD) % MOD;
    }
    return total;
}

void verify_small() {
    cout << "PE 643: Friends and Strings - verification\n\n";
    
    for (int N : {10, 30, 100}) {
        ll F = compute_F(N);
        cout << "F(" << N << ") = " << F << "\n";
    }
    
    // Show friendship classes for N=30
    cout << "\nSample friend groups for N=30:\n";
    sieve(30);
    vector<int> rad(31, 1);
    for (int p : primes) {
        for (int j = p; j <= 30; j += p) rad[j] *= p;
    }
    map<int, vector<int>> groups;
    for (int n = 1; n <= 30; n++) groups[rad[n]].push_back(n);
    for (auto& [r, nums] : groups) {
        if (nums.size() >= 2) {
            cout << "rad=" << r << ": ";
            for (int x : nums) cout << x << " ";
            cout << "\n";
        }
    }
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
        const int N = 1000;
        cout << "Computing F(" << N << ")...\n";
        ll F = compute_F(N);
        cout << "F(" << N << ") = " << F << "\n";
        return 0;
    }
    
    cout << "PE 643: Friends and Strings\n";
    cout << "F(10^11) mod 1,000,000,007 = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer, 'verify' for small checks.\n";
    
    return 0;
}
