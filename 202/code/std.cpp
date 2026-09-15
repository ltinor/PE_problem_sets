#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// PE 202 — Laserbeam
// Equilateral triangle mirrors, beam enters at vertex C, bounces b times, exits at C.
// Let n = (b+3)/2. If b is even (n not integer), answer = 0.
// Condition: count a in [1,n-1] with gcd(a,n)=1 and a%3 ≠ (n-a)%3.
// The excluded residue is r = (2*n)%3. Count coprimes NOT in this residue.

vector<ll> primes; // distinct prime factors of n

void factorize(ll n){
    primes.clear();
    for(ll p = 2; p*p <= n; p++){
        if(n % p == 0){
            primes.push_back(p);
            while(n % p == 0) n /= p;
        }
    }
    if(n > 1) primes.push_back(n);
}

// Extended Euclidean: returns gcd, and sets x,y such that ax + by = gcd
ll mygcd(ll a, ll b){
    while(b){ll t=b; b=a%b; a=t;}
    return a;
}

ll egcd(ll a, ll b, ll &x, ll &y){
    if(b == 0){x=1; y=0; return a;}
    ll g = egcd(b, a%b, y, x);
    y -= a/b * x;
    return g;
}

// Count numbers a in [1, n-1] with a ≡ r (mod 3) and gcd(a, n) = 1
// Uses inclusion-exclusion over distinct prime factors
ll count_coprime_mod(ll n, ll r){
    int k = primes.size();
    ll total = 0;

    // Iterate over all subsets of primes
    for(int mask = 0; mask < (1<<k); mask++){
        ll M = 1;
        int bits = 0;
        for(int i = 0; i < k; i++){
            if(mask & (1<<i)){
                M *= primes[i];
                bits++;
            }
        }

        // Count a in [1, n-1] with a ≡ r (mod 3) and a ≡ 0 (mod M)
        // Using CRT: solve a ≡ r (mod 3), a ≡ 0 (mod M)
        // If gcd(3,M) > 1 (i.e. 3|M), need special handling
        
        ll g = mygcd(3LL, M);
        ll L = 3LL / g * M; // lcm(3, M)

        // Check consistency: need r ≡ 0 (mod g)
        if(r % g != 0) continue; // no solution

        // Solve using CRT
        // a ≡ r (mod 3), a ≡ 0 (mod M)
        ll x, y;
        egcd(3, M, x, y);
        // 3*x + M*y = g
        // Solution: a₀ = (r * M * y + 0 * 3 * x) / g  mod L
        // Actually: a₀ ≡ r (mod 3), a₀ ≡ 0 (mod M)
        // Let a₀ = M * t. Then M*t ≡ r (mod 3) → t ≡ r * M^{-1} (mod 3/g)
        
        // M*y ≡ g (mod 3) → y is the inverse of M/g mod 3/g
        // a₀ = 0 * (3/g)*x + r * (M/g)*y  (mod L)
        // But since second congruence is 0: a₀ = r * (M/g) * y mod L
        
        ll a0 = (r % L) * ((M / g) % L) % L;
        a0 = (a0 * (y % L)) % L;
        a0 = (a0 % L + L) % L;

        // Count numbers a = a0 + k*L in [1, n-1]
        ll first;
        if(a0 == 0) first = L;
        else first = a0;
        
        ll cnt = 0;
        if(first <= n-1){
            cnt = (n - 1 - first) / L + 1;
        }

        // Inclusion-exclusion: add for even subset size, subtract for odd
        if(bits % 2 == 0) total += cnt;
        else total -= cnt;
    }

    return total;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll b;
    cin >> b;

    // Need n = (b+3)/2 integer → b must be odd
    if((b + 3) % 2 != 0){
        cout << "0\n";
        return 0;
    }

    ll n = (b + 3) / 2;
    if(n <= 1){
        cout << "0\n";
        return 0;
    }

    factorize(n);

    // 光束从 C 进入，方向 (a, n-a) 在展开网格中。
    // 到达顶点 (a, n-a) 是 C 副本当且仅当 a ≡ n-a (mod 3)
    // 即 2a ≡ n (mod 3)，即 a ≡ 2n (mod 3)（因 2 的逆元是 2）。
    // 答案 = #{a : 1≤a≤n-1, gcd(a,n)=1, a ≡ 2n (mod 3)}，无需除以 2。
    ll ans = count_coprime_mod(n, (2*n) % 3);
    cout << ans << "\n";
}
