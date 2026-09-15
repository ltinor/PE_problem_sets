#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 238: brute - for small K, verify by generating string and sliding window

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    const ll MOD = 20300713;
    ll s = 14025256;

    vector<int> digits;
    // Generate enough digits
    for (int gen = 0; gen < 50000; gen++) {
        string ds = to_string(s);
        for (char c : ds) digits.push_back(c - '0');
        s = (s * s) % MOD;
    }

    ll total = 0;
    ll M = digits.size();

    // For each target k, use sliding window to find earliest substring
    for (ll k = 1; k <= K; k++) {
        ll best = 0; // 0 means not found
        ll sum = 0;
        ll l = 0;
        for (ll r = 0; r < M; r++) {
            sum += digits[r];
            while (sum > k && l <= r) {
                sum -= digits[l];
                l++;
            }
            if (sum == k) {
                best = l + 1; // 1-indexed
                break;
            }
        }
        total += best;
    }

    cout << total << "\n";
    return 0;
}
