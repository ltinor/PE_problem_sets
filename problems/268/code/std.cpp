#include<bits/stdc++.h>
using namespace std;
#define ll long long
using i128 = __int128;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Primes < 100
    vector<int> primes;
    for (int i = 2; i < 100; i++) {
        bool is_prime = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) { is_prime = false; break; }
        }
        if (is_prime) primes.push_back(i);
    }

    int m = primes.size(); // 25

    // S[j] = sum of floor(N / product) for all subsets of size j
    vector<i128> S(m + 1, 0);

    // Enumerate all subsets
    int total = 1 << m;
    for (int mask = 1; mask < total; mask++) {
        i128 prod = 1;
        int bits = 0;
        bool overflow = false;
        
        for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) {
                bits++;
                prod *= primes[i];
                if (prod > N) {
                    overflow = true;
                    break;
                }
            }
        }
        
        if (!overflow) {
            S[bits] += N / (ll)prod;
        }
    }

    // Inclusion-Exclusion: at least 4
    // Precompute binomial coefficients
    vector<vector<i128>> C(m + 1, vector<i128>(m + 1, 0));
    for (int i = 0; i <= m; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
    }

    i128 ans = 0;
    for (int k = 4; k <= m; k++) {
        i128 coef = C[k-1][3]; // C(k-1, 3)
        if ((k - 4) % 2 == 0) {
            ans += coef * S[k];
        } else {
            ans -= coef * S[k];
        }
    }

    cout << (ll)ans << "\n";
    return 0;
}
