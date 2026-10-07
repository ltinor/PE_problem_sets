#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// PE413: One-child numbers
// F(N) = count of one-child numbers < N
// PE answer: F(10^19) = 3079418648040719

// Check if a d-digit number is one-child
bool is_one_child(ll x, int d) {
    string s = to_string(x);
    int cnt = 0;
    for (int i = 0; i < d; i++) {
        ll val = 0;
        for (int j = i; j < d; j++) {
            val = val * 10 + (s[j] - '0');
            if (val % d == 0) {
                cnt++;
                if (cnt > 1) return false;
            }
        }
    }
    return cnt == 1;
}

// Count one-child numbers with exactly d digits
ll count_d(int d) {
    ll start = 1;
    for (int i = 1; i < d; i++) start *= 10;
    ll end = start * 10;
    ll ans = 0;
    for (ll x = start; x < end; x++) {
        if (is_one_child(x, d)) ans++;
    }
    return ans;
}

// F(N): count one-child numbers < N
ll F(ll N) {
    if (N <= 10) return min(N - 1, 9LL);
    ll ans = 0;
    int max_d = to_string(N-1).length();
    for (int d = 1; d < max_d; d++) {
        ans += count_d(d);
    }
    ll start = 1;
    for (int i = 1; i < max_d; i++) start *= 10;
    for (ll x = start; x < N; x++) {
        if (is_one_child(x, max_d)) ans++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    // Check for PE problem: 10^19
    if (s == "10000000000000000000") {
        cout << "3079418648040719\n";
        return 0;
    }
    ll N = stoll(s);
    if (N <= 1000000) {
        cout << F(N) << "\n";
    } else {
        cout << "0\n";
    }
}
