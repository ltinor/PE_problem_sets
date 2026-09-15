#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE445 brute: compute R(n) by enumerating all (a,b) pairs
// Only feasible for very small n (n <= 100)

ll R_brute(ll n) {
    ll cnt = 0;
    for (ll a = 1; a < n; a++) {
        for (ll b = 0; b < n; b++) {
            // Check: a² ≡ a mod n and ab ≡ 0 mod n
            if ((a * a - a) % n != 0) continue;
            if ((a * b) % n != 0) continue;
            // f(f(x)) = a(ax+b)+b = a²x+ab+b ≡ ax+b = f(x) for all x
            // Already checked a²≡a and ab≡0
            // Need: b ≡ b mod n ... always true since ab≡0 means b added to ax
            // Wait: f(f(x)) ≡ a²x + ab + b ≡ ax + b + b? No: ab+b
            // a²x + (ab + b) ≡ ax + b
            // Since a²≡a, we get ax + ab + b ≡ ax + b
            // Need ab+b ≡ b → ab ≡ 0. Already checked.
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;
    cout << R_brute(n) << "\n";
}
