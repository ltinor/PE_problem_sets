#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll N;
        cin >> N;

        // Build spiral and sum diagonals (only for small N)
        // Using simulation: layer by layer
        ll sum = 1; // center
        for (ll k = 3; k <= N; k += 2) {
            // Top-right: k*k
            // Four corners of layer k
            sum += 4 * k * k - 6 * (k - 1);
        }
        cout << sum << "\n";
    }
    return 0;
}
