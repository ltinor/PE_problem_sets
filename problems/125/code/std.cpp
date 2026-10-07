#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool is_palindrome(ll x) {
    string s = to_string(x);
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    unordered_set<ll> seen;
    ll total = 0;

    // Max starting point: i such that i^2 < N
    ll max_start = (ll)sqrt(N);
    for (ll i = 1; i <= max_start; i++) {
        ll sum = i * i;
        for (ll j = i + 1; ; j++) {
            sum += j * j;
            if (sum >= N) break;
            if (is_palindrome(sum) && !seen.count(sum)) {
                seen.insert(sum);
                total += sum;
            }
        }
    }

    cout << total << "\n";
    return 0;
}
