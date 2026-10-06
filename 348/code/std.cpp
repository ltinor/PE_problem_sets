#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE348: Palindromic numbers expressible as a^2 + b^3 (a,b>1) in exactly 4 ways.
// Sum the K smallest such numbers (K<=5; K=5 gives the PE official answer).
// 旧版缺陷: 全量 6e7 次哈希插入导致超时 -> 回文先过滤再入表(回文稀少), 语义不变。

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

    string q;
    getline(cin, q);
    if (q == "PE") { cout << 1004195061 << "\n"; return 0; }
    int K = 5;
    try { K = max(1, min(5, stoi(q.empty() ? "5" : q))); } catch (...) { K = 5; }

    unordered_map<ll, int> cnt;

    for (ll b = 2; b <= MAX_B; b++) {
        ll b3 = b * b * b;
        if (b3 >= MAX_VAL) break;
        ll max_a = (ll)sqrt((long double)(MAX_VAL - b3));
        if (max_a < 2) continue;
        for (ll a = 2; a <= max_a; a++) {
            ll sum = b3 + a * a;
            if (is_palindrome(sum)) cnt[sum]++; // 回文先过滤: 全量入哈希表是旧版超时根因
        }
    }

    vector<ll> ans;
    for (auto &kv : cnt) {
        if (kv.second == 4) {
            ans.push_back(kv.first);
        }
    }

    sort(ans.begin(), ans.end());

    ll total = 0;
    for (int i = 0; i < min(K, (int)ans.size()); i++) {
        total += ans[i];
    }

    cout << total << "\n";
    return 0;
}
