#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force same algorithm as std but simpler
// Suitable for K <= 200

bool is_non_divisor(ll n) {
    ll a = 1 % n, b = 1 % n, c = 1 % n;
    if(a == 0 || b == 0 || c == 0) return false;

    set<ll> seen;
    seen.insert(a * n * n + b * n + c);

    for(ll step = 0; step < n * n; step++) {
        ll next = (a + b + c) % n;
        if(next == 0) return false;
        a = b; b = c; c = next;
        ll state = a * n * n + b * n + c;
        if(seen.count(state)) return true;
        seen.insert(state);
    }
    return true; // conservative
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    ll cnt = 0;
    for(ll n = 1; ; n += 2) {
        if(is_non_divisor(n)) {
            cnt++;
            if(cnt == K) {
                cout << n << "\n";
                return 0;
            }
        }
    }
    return 0;
}
