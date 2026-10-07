#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: check all (a,b,c) with a+b+c ≤ N
// Uses the condition 8a³+15a²+6a-1 = 27b²c
int main(int argc, char* argv[]) {
    ll N = 1000;
    if (argc > 1) N = atoll(argv[1]);

    ll ans = 0;
    for (ll a = 1; a <= N - 2; a++) {
        if (a % 3 != 2) continue; // only a ≡ 2 mod 3
        for (ll b = 1; a + b <= N - 1; b++) {
            ll lhs = 8*a*a*a + 15*a*a + 6*a - 1;
            if (lhs % 27 != 0) continue;
            ll rhs = lhs / 27;
            if (rhs % (b*b) != 0) continue;
            ll c = rhs / (b*b);
            if (c >= 1 && a + b + c <= N) {
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
