#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 341: Sum of G(n^3) for 1 ≤ n < N
// Golomb's self-describing sequence: G(n) is nondecreasing,
// value k appears exactly G(k) times.
//
// O(N^(2/3)) algorithm:
// 1. Precompute G[1..M] and prefix sums P[1..M] where M ~ N^(2/3)
// 2. For larger n, use the generating method with group counting
//
// For OJ: N ≤ 3000 (max n^3 ≈ 2.7e10, need G up to ~3.4e6 values)

const int MAXM = 5000000; // 5 million entries for G
int G[MAXM + 1];
ll P[MAXM + 1]; // prefix sums of G

void generate_G(int M) {
    G[1] = 1;
    P[1] = 1;
    int cur = 1;  // current value being placed
    int rem = 1;  // remaining occurrences of cur
    for (int i = 2; i <= M; i++) {
        if (rem == 0) {
            cur++;
            rem = G[cur];
        }
        G[i] = cur;
        rem--;
        P[i] = P[i-1] + G[i];
    }
}

// Find G(n) using binary search on prefix sums
int find_G(ll n, int M) {
    if (n <= M) return G[n];
    // Binary search on P to find the range
    int lo = 1, hi = M;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (P[mid] < n) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

ll compute_sum(int N) {
    // N is max n (exclusive): sum for n=1..N-1
    if (N <= 1) return 0;
    
    // Determine M needed: need P[M] >= (N-1)^3
    ll max_n3 = (ll)(N-1) * (N-1) * (N-1);
    
    // Calculate how large M needs to be
    int M = MAXM;
    if (max_n3 > P[MAXM]) {
        // Need more entries - estimate needed M
        // P[M] ≈ 0.74 * M^1.618
        // M ≈ (P/0.74)^(1/1.618)
        M = (int)pow(max_n3 / 0.74, 1.0 / 1.618) + 1000000;
        M = min(M, MAXM);
    }
    
    generate_G(M);
    
    ll ans = 0;
    for (ll n = 1; n < N; n++) {
        ll n3 = n * n * n;
        ans += find_G(n3, M);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    cout << compute_sum(N) << "\n";
    return 0;
}
