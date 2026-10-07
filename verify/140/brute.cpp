#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Brute force: same recurrence as std

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    vector<ll> N(K + 1);
    if (K >= 1) N[1] = 2;
    if (K >= 2) N[2] = 5;
    if (K >= 3) N[3] = 21;
    if (K >= 4) N[4] = 42;

    for (int i = 5; i <= K; i++) {
        N[i] = 7 * N[i - 2] - N[i - 4] + 7;
    }

    ll sum = 0;
    for (int i = 1; i <= K; i++) {
        sum += N[i];
    }

    cout << sum << "\n";
    return 0;
}
