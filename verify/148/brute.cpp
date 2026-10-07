#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Brute force: generate Pascal's triangle row by row
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll R;
    cin >> R;

    ll ans = 0;

    // Generate Pascal's triangle row by row
    vector<int> row;
    for (ll n = 0; n < R; n++) {
        vector<int> next_row;
        next_row.push_back(1);
        for (ll k = 1; k < n; k++) {
            int val = (row[k-1] + row[k]) % 7;
            next_row.push_back(val);
        }
        if (n > 0) next_row.push_back(1);

        // Count non-zero entries in this row
        for (int x : next_row) {
            if (x != 0) ans++;
        }

        row = next_row;
    }

    cout << ans << "\n";
    return 0;
}
