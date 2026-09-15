#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 157: Diophantine Equation 1/a + 1/b = p/10^n
// Let a = g·x, b = g·y where gcd(x,y)=1, x≤y
// Then: 10^n·(x+y) = p·g·x·y
// Since gcd(x+y, xy)=1, we have xy | 10^n
// So x, y are powers of 2 and 5, with gcd(x,y)=1
// Let k = 10^n/(xy), then p·g = k·(x+y)
// Number of solutions = d(k·(x+y)) where d is divisor count

ll my_gcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

ll count_divisors(ll n) {
    ll cnt = 0;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            if (i * i != n) cnt++;
        }
    }
    return cnt;
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

        // Enumerate x = 2^i·5^j where i,j ≤ n (but xy must divide 10^n)
        // Actually, since xy | 10^n, x = 2^a·5^b, y = 2^c·5^d with a+c≤n, b+d≤n
        // And gcd(x,y)=1 means they can't share factors: 
        // either a=0 or c=0, and either b=0 or d=0

        // Generate all possible x values (divisors of 10^n)
        vector<ll> divisors;
        for (int i2 = 0; i2 <= n; i2++) {
            for (int i5 = 0; i5 <= n; i5++) {
                ll x = 1;
                for (int k = 0; k < i2; k++) x *= 2;
                for (int k = 0; k < i5; k++) x *= 5;
                if (x <= pow10) divisors.push_back(x);
            }
        }

        // Sort and remove duplicates
        sort(divisors.begin(), divisors.end());
        divisors.erase(unique(divisors.begin(), divisors.end()), divisors.end());

        // For each pair (x, y) where x·y|10^n, gcd(x,y)=1, x≤y
        for (ll x : divisors) {
            for (ll y : divisors) {
                if (x > y) continue;
                if (my_gcd(x, y) != 1) continue;
                if ((x * y) > pow10) continue;
                if (pow10 % (x * y) != 0) continue;

                ll k = pow10 / (x * y);
                ll m = k * (x + y);
                total += count_divisors(m);
            }
        }
    }

    cout << total << "\n";
    return 0;
}
