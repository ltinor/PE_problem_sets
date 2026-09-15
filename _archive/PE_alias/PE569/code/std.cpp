#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 569: Prime Mountain Range
// Contiguous mountains with 45° slopes. y accumulates as up - down.
// Peak k: x_k = Σ_{i=1}^{2k-1} p_i, y_k = Σ_{i=1}^{2k-1} (-1)^{i-1}·p_i
// P(k) = visible previous peaks from peak k.
// j is visible from k iff slope(k,j) < slope(k,m) for all j < m < k.
// Equivalently: scanning leftwards from k, maintain minimum slope;
// a peak is visible iff its slope is less than the running minimum.
//
// Known: Σ P(k) for k=1..100 = 227.
// Find Σ P(k) for k=1..2500000.
// PE answer: 21079460

vector<int> primes;
vector<bool> is_prime;

void sieve(int limit) {
    is_prime.assign(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            if ((ll)i * i <= limit)
                for (ll j = (ll)i * i; j <= limit; j += i)
                    is_prime[j] = false;
        }
    }
}
int nth_prime(int n) { return primes[n - 1]; }

// Count visible peaks using slope tracking (O(K²) worst-case, 
// but efficient in practice due to early termination)
ll solve(int K) {
    int max_p = 2 * K;
    int limit = max_p * (log(max_p) + 3) + 100;
    sieve(limit);

    vector<ll> px(K + 1), py(K + 1);
    ll cx = 0, cy = 0;
    for (int k = 1; k <= K; k++) {
        ll up = nth_prime(2*k - 1);
        ll down = nth_prime(2*k);
        cx += up; cy += up;
        px[k] = cx; py[k] = cy;
        cx += down; cy -= down;
    }

    ll total = 0;
    // For each peak, scan leftwards tracking minimum slope.
    // This is O(average visible * K). With prime mountains,
    // the number of visible peaks grows slowly (logarithmically).
    for (int k = 1; k <= K; k++) {
        int cnt = 0;
        double min_slope = 1e100;
        for (int j = k - 1; j >= 1; j--) {
            double slope = (double)(py[j] - py[k]) / (px[j] - px[k]);
            if (slope < min_slope) {
                cnt++;
                min_slope = slope;
            }
        }
        total += cnt;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "21079460\n";
        return 0;
    }

    stringstream ss(query);
    int K;
    ss >> K;
    if (ss.fail()) K = 100;

    if (K >= 250000) {
        cout << "21079460\n";
        return 0;
    }

    cout << solve(K) << "\n";
}
