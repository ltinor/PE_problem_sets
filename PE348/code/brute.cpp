#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE348 brute: same as std
bool is_palindrome(ll x) {
    string s = to_string(x);
    for (int i = 0, j = s.size()-1; i < j; i++, j--)
        if (s[i] != s[j]) return false;
    return true;
}

int main() {
    const ll MAX_VAL = 5000000000LL;
    const ll MAX_B = 2000;
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
    for (int i = 0; i < min(5, (int)ans.size()); i++) total += ans[i];
    cout << total << "\n";
}
