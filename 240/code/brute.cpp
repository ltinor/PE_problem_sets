#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 240 brute: enumerate all S^N combinations for small N, S

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S, K, T;
    cin >> N >> S >> K >> T;

    if (N > 6 || S > 8) { cout << "0\n"; return 0; }

    vector<int> dice(N, 1);
    ll ans = 0;

    // Enumerate all S^N possibilities
    ll total = 1;
    for (int i = 0; i < N; i++) total *= S;

    for (ll mask = 0; mask < total; mask++) {
        ll tmp = mask;
        for (int i = 0; i < N; i++) {
            dice[i] = (tmp % S) + 1;
            tmp /= S;
        }

        // Find top K sum
        sort(dice.begin(), dice.end(), greater<int>());
        int sum = 0;
        for (int i = 0; i < K; i++) sum += dice[i];
        if (sum == T) ans++;
    }

    cout << ans << "\n";
    return 0;
}
