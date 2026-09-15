#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE413 brute: one-child numbers via enumeration (same logic, slower)
// But verified against std for small inputs

bool is_one_child(ll x, int d) {
    string s = to_string(x);
    int cnt = 0;
    for (int i = 0; i < d; i++) {
        ll val = 0;
        for (int j = i; j < d; j++) {
            val = val * 10 + (s[j] - '0');
            if (val % d == 0) cnt++;
            if (cnt > 1) return false;
        }
    }
    return cnt == 1;
}

ll F_brute(ll N) {
    ll ans = 0;
    for (ll x = 1; x < N; x++) {
        int d = to_string(x).length();
        if (is_one_child(x, d)) ans++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    cout << F_brute(N) << "\n";
}
