#include<bits/stdc++.h>
using namespace std;
#define ll long long
// Brute: generate weak Goodstein sequence for small n
ll to_base(ll num, ll base) {
    // convert num to base representation, interpret as base+1
    ll result = 0, p=1;
    while (num) {
        result += (num % base) * p;
        num /= base;
        p *= (base+1);
    }
    return result;
}

int main() {
    ll N; cin >> N;
    ll total = 0;
    for (ll n=1; n<N; n++) {
        ll cnt = 0, g = n, k = 2;
        while (g > 0) {
            cnt++;
            g = to_base(g, k) - 1;
            k++;
        }
        total += cnt;
    }
    cout << total << "\n";
}
