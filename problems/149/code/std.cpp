#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Lagged Fibonacci generator for PE 149
// s_k = s_{k-24} + s_{k-55} mod 1000000, then -500000
// s_1..s_55 given by: s_k = (100003 - 200003*k + 300007*k^3) mod 1000000 - 500000
// Fill N×N matrix row by row

// Kadane's algorithm: max subarray sum
ll kadane(const vector<ll>& arr) {
    ll max_ending = 0, max_so_far = 0;
    for (ll x : arr) {
        max_ending = max(0LL, max_ending + x);
        max_so_far = max(max_so_far, max_ending);
    }
    return max_so_far;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // Generate the sequence
    int total = N * N;
    vector<ll> s(max(total, 55) + 1);

    // First 55 terms
    for (int k = 1; k <= 55; k++) {
        ll val = 100003 - 200003LL * k + 300007LL * k * k * k;
        val = val % 1000000;
        if (val < 0) val += 1000000;
        s[k] = val - 500000;
    }

    // Generate remaining
    for (int k = 56; k <= total; k++) {
        s[k] = (s[k-24] + s[k-55] + 1000000) % 1000000 - 500000;
    }

    // Fill matrix row by row
    vector<vector<ll>> mat(N, vector<ll>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mat[i][j] = s[i * N + j + 1];
        }
    }

    ll ans = 0;

    // Horizontal
    for (int i = 0; i < N; i++) {
        ans = max(ans, kadane(mat[i]));
    }

    // Vertical
    for (int j = 0; j < N; j++) {
        vector<ll> col(N);
        for (int i = 0; i < N; i++) col[i] = mat[i][j];
        ans = max(ans, kadane(col));
    }

    // Diagonal (top-left to bottom-right)
    // Main diagonal and shifted
    for (int d = 0; d < N; d++) {
        vector<ll> diag;
        for (int i = 0; i + d < N; i++) {
            diag.push_back(mat[i][i + d]);
        }
        ans = max(ans, kadane(diag));
    }
    for (int d = 1; d < N; d++) {
        vector<ll> diag;
        for (int i = 0; i + d < N; i++) {
            diag.push_back(mat[i + d][i]);
        }
        ans = max(ans, kadane(diag));
    }

    // Anti-diagonal (top-right to bottom-left)
    for (int d = 0; d < N; d++) {
        vector<ll> diag;
        for (int i = 0; i + d < N; i++) {
            diag.push_back(mat[i][N - 1 - i - d]);
        }
        ans = max(ans, kadane(diag));
    }
    for (int d = 1; d < N; d++) {
        vector<ll> diag;
        for (int i = 0; i + d < N; i++) {
            diag.push_back(mat[i + d][N - 1 - i]);
        }
        ans = max(ans, kadane(diag));
    }

    cout << ans << "\n";
    return 0;
}
