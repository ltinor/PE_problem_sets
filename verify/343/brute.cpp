#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long

// Brute force: simulate the sequence for each k^3
ll f_brute(ll k) {
    ll n = k * k * k;
    ll x = 1, y = n;
    while (y > 1) {
        x++;
        y--;
        ull a = x, b = y;
        while (b) { ull t = a % b; a = b; b = t; }
        ull g = a;
        x /= (ll)g;
        y /= (ll)g;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int K;
    cin >> K;
    
    ll ans = 0;
    for (int k = 1; k <= K; k++) {
        ans += f_brute(k);
    }
    
    cout << ans << "\n";
    return 0;
}
