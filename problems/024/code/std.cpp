#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll fact[11];

// Cantor expansion: find K-th permutation of 0..N-1 (1-indexed)
void solve(int N, ll K) {
    K--; // convert to 0-indexed
    vector<bool> used(N, false);
    for (int pos = 0; pos < N; pos++) {
        ll f = fact[N - 1 - pos];
        int idx = K / f;
        K %= f;
        // find idx-th unused digit
        int cnt = 0;
        for (int digit = 0; digit < N; digit++) {
            if (!used[digit]) {
                if (cnt == idx) {
                    cout << digit;
                    used[digit] = true;
                    break;
                }
                cnt++;
            }
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i <= 10; i++) fact[i] = fact[i-1] * i;

    int T;
    cin >> T;
    while (T--) {
        int N; ll K;
        cin >> N >> K;
        solve(N, K);
    }
}
