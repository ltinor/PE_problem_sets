#include<bits/stdc++.h>
using namespace std;

#define ll long long

bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Extended Euclidean: ax + by = gcd(a,b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

ll mod_inv(ll a, ll m) {
    ll x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    // Generate all primes up to next prime after M
    vector<int> primes;
    for (int i = 2; ; i++) {
        if (is_prime(i)) {
            primes.push_back(i);
            if (i > M && primes.size() >= 2) {
                // We have enough primes to cover p1 <= M
                if (primes[primes.size()-2] > M) break;
            }
        }
    }

    __int128 ans = 0;

    for (int i = 0; i < (int)primes.size() - 1; i++) {
        int p1 = primes[i];
        if (p1 < 5) continue;
        if (p1 > M) break;

        int p2 = primes[i + 1];

        // Find smallest S such that S ends with p1 and S % p2 == 0
        // S = p1 + k * 10^len(p1), find k s.t. (p1 + k * pow10) % p2 == 0
        // k * pow10 ≡ -p1 (mod p2)
        // k ≡ -p1 * inv(pow10, p2) (mod p2)

        // Compute pow10 = 10^len(p1)
        int len = to_string(p1).length();
        ll pow10 = 1;
        for (int j = 0; j < len; j++) pow10 *= 10;

        ll inv = mod_inv(pow10 % p2, p2);
        ll k = ((-p1 % p2) + p2) % p2;
        k = (k * inv) % p2;

        __int128 S = (__int128)p1 + (__int128)k * pow10;
        ans += S;
    }

    // Print __int128
    string s;
    if (ans == 0) s = "0";
    while (ans > 0) {
        s = char('0' + (int)(ans % 10)) + s;
        ans /= 10;
    }
    cout << s << "\n";

    return 0;
}
