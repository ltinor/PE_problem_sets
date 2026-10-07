#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force for PE 157: enumerate a, b up to limit
ll my_gcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    ll total = 0;

    for (int n = 1; n <= N; n++) {
        ll pow10 = 1;
        for (int i = 0; i < n; i++) pow10 *= 10;

        ll cnt = 0;
        // a <= b. Upper bound: a can't exceed 2*10^n
        ll max_ab = 10 * pow10; // safe upper bound for small n
        for (ll a = 1; a <= max_ab; a++) {
            for (ll b = a; b <= max_ab; b++) {
                // Check if 1/a + 1/b = p/10^n for some integer p
                // (a+b)/ab = p/10^n => 10^n(a+b) must be divisible by ab
                ll num = pow10 * (a + b);
                if (num % (a * b) == 0) {
                    cnt++;
                }
            }
        }
        total += cnt;
    }

    cout << total << "\n";
    return 0;
}
