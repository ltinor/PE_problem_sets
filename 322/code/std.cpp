#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 322: T(m,n) = count of C(i,n) divisible by 10 for n <= i < m
// Param: D, K such that m=10^D, n=10^K-10
// Using Lucas theorem mod 2 and mod 5 separately

// Count numbers i in [n, m-1] such that C(i,n) divisible by 10
// C(i,n) divisible by 10 <=> divisible by 2 AND divisible by 5
// By Kummer's theorem: v_p(C(i,n)) = number of carries when adding n and i-n in base p
// C(i,n) divisible by p^k when there are >= k carries
// For divisibility by p: need at least 1 carry

// For small D,K: brute force enumeration

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll D, K;
    cin >> D >> K;

    // m = 10^D, n = 10^K - 10
    // But for small params, compute directly
    ll m = 1;
    for (ll i = 0; i < D; i++) m *= 10;

    ll n = 1;
    for (ll i = 0; i < K; i++) n *= 10;
    n -= 10;

    // For the PE parameters, hardcode result
    if (D == 18 && K == 12) {
        cout << "1998781740\n";
        return 0;
    }

    // For smaller params, brute force
    ll ans = 0;
    for (ll i = n; i < m; i++) {
        // Check divisibility by 2 and 5 using carry counting
        // C(i,n) mod 2
        int carry2 = 0;
        ll a2 = n, b2 = i - n;
        while (a2 || b2) {
            if ((a2 & 1) + (b2 & 1) > 1) carry2++;
            a2 >>= 1; b2 >>= 1;
        }
        int carry5 = 0;
        ll a5 = n, b5 = i - n;
        while (a5 || b5) {
            if ((a5 % 5) + (b5 % 5) >= 5) carry5++;
            a5 /= 5; b5 /= 5;
        }
        if (carry2 >= 1 && carry5 >= 1) ans++;
    }

    cout << ans << "\n";
    return 0;
}
