#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    // Compute rad(n) for n=1..N using sieve
    vector<int> rad(N + 1, 1);
    for (int i = 2; i <= N; i++) {
        if (rad[i] == 1) { // prime
            for (int j = i; j <= N; j += i) {
                rad[j] *= i;
            }
        }
    }

    // Create pairs (rad, n) and sort
    vector<pair<int, int>> v;
    for (int n = 1; n <= N; n++) {
        v.push_back({rad[n], n});
    }
    sort(v.begin(), v.end());

    cout << v[K - 1].second << "\n";
    return 0;
}
