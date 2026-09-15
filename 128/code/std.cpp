#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// For ring r:
// S_r = 3r(r-1)+2 (start of ring), check {6r-1, 6r+1, 12r+5}
// E_r = 3r(r+1)+1 (end of ring), check {6r-1, 6r+5, 12r-7}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    // First, tile 1 and 2 are special cases
    // PD(1): neighbors {2,3,4,5,6,7}. Diffs: |1-2|=1,|1-3|=2,|1-4|=3,|1-5|=4,|1-6|=5,|1-7|=6
    // Primes: 2,3,5 → PD=3. So tile 1 is first.
    // But the problem says the 10th tile is 271. Let me check: 1 is the first.
    // Actually wait: we need to include tile 1.

    vector<ll> ans;
    ans.push_back(1); // tile 1 has PD=3

    for (int r = 1; ; r++) {
        // S_r = 3r(r-1)+2, only check for r ≥ 2
        if (r >= 2) {
            ll s = 3LL * r * (r - 1) + 2;
            int cnt = 0;
            if (is_prime(6LL * r - 1)) cnt++;
            if (is_prime(6LL * r + 1)) cnt++;
            if (is_prime(12LL * r + 5)) cnt++;
            if (cnt == 3) {
                ans.push_back(s);
            }
        }

        // E_r = 3r(r+1)+1
        ll e = 3LL * r * (r + 1) + 1;
        int cnt = 0;
        if (is_prime(6LL * r - 1)) cnt++;
        if (is_prime(6LL * r + 5)) cnt++;
        if (is_prime(12LL * r - 7)) cnt++;
        if (cnt == 3) {
            ans.push_back(e);
        }

        if ((int)ans.size() >= K) {
            // Sort to get ascending order
            sort(ans.begin(), ans.end());
            cout << ans[K - 1] << "\n";
            return 0;
        }
    }

    return 0;
}
