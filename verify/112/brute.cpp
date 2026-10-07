#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Independent brute: uses string-based approach
bool is_bouncy_brute(ll x) {
    string s = to_string(x);
    if (s.size() <= 1) return false;
    bool inc = true, dec = true;
    for (int i = 1; i < (int)s.size(); i++) {
        if (s[i] < s[i-1]) inc = false;
        if (s[i] > s[i-1]) dec = false;
    }
    return !inc && !dec;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P;
    cin >> P;

    ll cnt = 0;
    for (ll n = 1; ; n++) {
        if (is_bouncy_brute(n)) cnt++;
        if (cnt * 100 >= P * n) {
            cout << n << "\n";
            break;
        }
    }
    return 0;
}
