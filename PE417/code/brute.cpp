#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE417 brute: compute cycle length of 1/n via long division simulation

ll L_brute(ll n) {
    // Remove factors 2 and 5
    while (n % 2 == 0) n /= 2;
    while (n % 5 == 0) n /= 5;
    if (n == 1) return 0;
    // Simulate long division: track remainders
    map<ll, ll> pos;
    ll rem = 1, idx = 0;
    while (rem && !pos.count(rem)) {
        pos[rem] = idx++;
        rem = (rem * 10) % n;
    }
    if (rem == 0) return 0;
    return idx - pos[rem];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    ll sum = 0;
    for (ll n = 3; n <= N; n++) sum += L_brute(n);
    cout << sum << "\n";
}
