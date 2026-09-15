#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: generate Thue-Morse up to enough terms,
// check which numbers appear as subsequence, verify A_n values.

// Generate first L terms of Thue-Morse
vector<int> gen_tm(int L) {
    vector<int> tm(L);
    for (int i = 0; i < L; i++)
        tm[i] = __builtin_popcount(i) & 1;
    return tm;
}

// Check if binary string s (MSB first) appears as subsequence in tm
bool is_subseq(const vector<int>& tm, const string& s) {
    int idx = 0;
    for (int x : tm) {
        if (idx < (int)s.size() && (s[idx] - '0') == x)
            idx++;
    }
    return idx == (int)s.size();
}

// Brute force: find n-th valid number by checking all numbers sequentially
ll brute_nth(ll n) {
    if (n == 0) return 0;
    int L = 200000; // enough for small verification
    auto tm = gen_tm(L);
    ll cnt = 0;
    for (ll x = 0; ; x++) {
        string bin;
        if (x == 0) bin = "0";
        else {
            ll t = x;
            while (t) { bin += (char)('0' + (t & 1)); t >>= 1; }
            reverse(bin.begin(), bin.end());
        }
        if (is_subseq(tm, bin)) {
            if (cnt == n) return x;
            cnt++;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // Small N only for brute verification
    for (int k = 1; k <= N; k++) {
        ll pow10 = 1;
        for (int i = 0; i < k; i++) pow10 *= 10;
        ll val = brute_nth(pow10);
        cout << val << "\n";
    }
    return 0;
}
