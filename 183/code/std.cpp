#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Check if (N/k)^k is a terminating decimal
// It's terminating iff after removing all factors of 2 and 5 from k,
// the remaining part divides N.
bool is_terminating(int N, int k) {
    int kk = k;
    while (kk % 2 == 0) kk /= 2;
    while (kk % 5 == 0) kk /= 5;
    return N % kk == 0;
}

// Find optimal k that maximizes (N/k)^k
// Optimal k is near N/e, check floor and ceil
int best_k(int N) {
    // k = round(N / e), where e ≈ 2.718281828
    double e = 2.718281828459045;
    int k1 = max(1, (int)floor(N / e));
    int k2 = max(1, (int)ceil(N / e));

    // Also check neighbors in case of floating point issues
    vector<int> candidates;
    for (int k = max(1, k1 - 2); k <= min(N, k2 + 2); k++) {
        candidates.push_back(k);
    }

    int best = 1;
    double best_val = 0;
    for (int k : candidates) {
        double val = k * log((double)N / k);
        if (val > best_val + 1e-12) {
            best_val = val;
            best = k;
        }
    }
    return best;
}

int D(int N) {
    int k = best_k(N);
    if (is_terminating(N, k)) return -N;
    else return N;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        ll sum = 0;
        for (int i = 5; i <= N; i++) {
            sum += D(i);
        }
        cout << sum << "\n";
    }

    return 0;
}
