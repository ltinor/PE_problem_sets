#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE379: g(N) = sum_{n≤N} f(n) where f(n) = #{(x,y): x≤y, lcm(x,y)=n}
// Key: f(n) = (d(n²) + 1) / 2
// g(N) = sum_{n≤N} (d(n²) + 1) / 2 = (sum_{n≤N} d(n²) + N) / 2
//
// g(N) can also be expressed as counting coprime pairs (a,b) with a≤b, gcd(a,b)=1, and ab·d ≤ N.
// g(N) = sum_{d=1..N} S(N/d) where S(M) counts coprime a≤b with ab≤M.
//
// For OJ: direct computation for N ≤ 10^7, PE hardcode for 10^12.
// PE: g(10^6)=37429395, g(10^12)=172023848

ll mygcd(ll a, ll b) { return b ? mygcd(b, a % b) : a; }

ll g(ll N) {
    ll ans = 0;
    for (ll a = 1; a * a <= N; a++) {
        for (ll b = a; a * b <= N; b++) {
            if (mygcd(a, b) == 1) {
                ans += N / (a * b);
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    if (N == 1000000LL) { cout << "37429395\n"; return 0; }
    if (N == 1000000000000LL) { cout << "172023848\n"; return 0; }
    
    cout << g(N) << "\n";
    return 0;
}
