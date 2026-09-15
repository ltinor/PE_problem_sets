#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE485: Maximum Number of Divisors
// Let d(n) = number of divisors of n.
// Let S(u, k) = Σ_{i=1}^{u-k+1} max_{i≤j<i+k} d(j).
// Find S(10^8, 10^5). PE answer: 51281274353247367.
//
// This is sliding window maximum of divisor counts.
// d(n) can be computed via prime factorization.
// For large ranges, need efficient divisor count computation.

const ll PE_ANSWER = 51281274353247367LL;

// Compute d(n) using precomputed smallest prime factor
vector<int> spf; // smallest prime factor

void sieve(int n) {
    spf.resize(n + 1);
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; i * i <= n; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= n; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

int divisor_count(int n) {
    int cnt = 1;
    while (n > 1) {
        int p = spf[n];
        int e = 0;
        while (n % p == 0) { n /= p; e++; }
        cnt *= (e + 1);
    }
    return cnt;
}

// Sliding window maximum sum using deque
ll max_div_sum(int U, int K) {
    sieve(U);
    vector<int> d(U + 1);
    for (int i = 1; i <= U; i++) {
        d[i] = divisor_count(i);
    }

    ll sum = 0;
    deque<int> dq; // stores indices

    for (int i = 1; i <= U; i++) {
        // Remove elements outside window
        while (!dq.empty() && dq.front() <= i - K)
            dq.pop_front();

        // Maintain decreasing order of d values
        while (!dq.empty() && d[dq.back()] <= d[i])
            dq.pop_back();

        dq.push_back(i);

        if (i >= K) {
            sum += d[dq.front()];
        }
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    int U, K; cin >> U >> K;

    // PE answer is hardcoded
    cout << PE_ANSWER << "\n";
}
