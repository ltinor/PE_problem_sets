#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE348: Palindromic numbers expressible as a^2 + b^3 (a,b>1) in exactly 4 ways.
// Sum the 5 smallest such numbers.

bool is_palindrome(ll x) {
    string s = to_string(x);
    for (int i = 0, j = s.size()-1; i < j; i++, j--)
        if (s[i] != s[j]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Need to find 5 smallest palindromic numbers with exactly 4 representations
    // Largest known is ~10^9 range, use generous bounds
    const ll MAX_VAL = 5000000000LL; // 5e9 should capture 5th number
    const ll MAX_B = 2000;           // b^3 up to 8e9

    unordered_map<ll, int> cnt;

    for (ll b = 2; b <= MAX_B; b++) {
        ll b3 = b * b * b;
        if (b3 >= MAX_VAL) break;
        ll max_a = (ll)sqrt((long double)(MAX_VAL - b3));
        if (max_a < 2) continue;
        for (ll a = 2; a <= max_a; a++) {
            ll sum = b3 + a * a;
            cnt[sum]++;
        }
    }

    vector<ll> ans;
    for (auto &kv : cnt) {
        if (kv.second == 4 && is_palindrome(kv.first)) {
            ans.push_back(kv.first);
        }
    }

    sort(ans.begin(), ans.end());

    ll total = 0;
    for (int i = 0; i < min(5, (int)ans.size()); i++) {
        total += ans[i];
    }

    cout << total << "\n";
    return 0;
}
