#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Brute force: O(N^3) max subarray for all directions
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int total = N * N;
    vector<ll> s(max(total, 55) + 1);

    for (int k = 1; k <= 55; k++) {
        ll val = 100003 - 200003LL * k + 300007LL * k * k * k;
        val = val % 1000000;
        if (val < 0) val += 1000000;
        s[k] = val - 500000;
    }

    for (int k = 56; k <= total; k++) {
        s[k] = (s[k-24] + s[k-55] + 1000000) % 1000000 - 500000;
    }

    vector<vector<ll>> mat(N, vector<ll>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mat[i][j] = s[i * N + j + 1];
        }
    }

    ll ans = 0;

    // O(N^3) brute for all directions
    auto max_subarray = [&](const vector<ll>& arr) -> ll {
        ll best = 0;
        for (int i = 0; i < (int)arr.size(); i++) {
            ll sum = 0;
            for (int j = i; j < (int)arr.size(); j++) {
                sum += arr[j];
                best = max(best, sum);
            }
        }
        return best;
    };

    // Horizontal
    for (int i = 0; i < N; i++) {
        ans = max(ans, max_subarray(mat[i]));
    }

    // Vertical
    for (int j = 0; j < N; j++) {
        vector<ll> col(N);
        for (int i = 0; i < N; i++) col[i] = mat[i][j];
        ans = max(ans, max_subarray(col));
    }

    // Diagonals
    for (int d = 0; d < N; d++) {
        vector<ll> diag;
        for (int i = 0; i + d < N; i++) diag.push_back(mat[i][i + d]);
        ans = max(ans, max_subarray(diag));
    }
    for (int d = 1; d < N; d++) {
        vector<ll> diag;
        for (int i = 0; i + d < N; i++) diag.push_back(mat[i + d][i]);
        ans = max(ans, max_subarray(diag));
    }

    // Anti-diagonals
    for (int d = 0; d < N; d++) {
        vector<ll> diag;
        for (int i = 0; i + d < N; i++) diag.push_back(mat[i][N - 1 - i - d]);
        ans = max(ans, max_subarray(diag));
    }
    for (int d = 1; d < N; d++) {
        vector<ll> diag;
        for (int i = 0; i + d < N; i++) diag.push_back(mat[i + d][N - 1 - i]);
        ans = max(ans, max_subarray(diag));
    }

    cout << ans << "\n";
    return 0;
}
