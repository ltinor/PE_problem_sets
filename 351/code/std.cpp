#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE351: Hexagonal orchards
// H(n) = 6 * sum_{k=1}^{n} (k - phi(k))
//      = 6 * (n*(n+1)/2 - sum_{k=1}^{n} phi(k))
// Visible points from center form a star-of-David-like pattern
// A point in the triangular lattice is visible iff gcd of its 
// hexagonal coordinates (a,b,c) with a+b+c=0 is 1.
// In axial coordinates (x,y): visible iff gcd(x,y) = 1.
// H(n) = total points - visible points = 6 * sum_{k=1}^{n} (k - phi(k))

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Linear sieve for phi up to N
    vector<int> phi(N + 1);
    vector<int> primes;
    primes.reserve(N / 10);
    
    phi[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (phi[i] == 0) {
            phi[i] = i - 1;
            primes.push_back(i);
        }
        for (int p : primes) {
            if ((ll)i * p > N) break;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }

    // H(n) = 6 * (n*(n+1)/2 - sum phi(1..n))
    __int128 total = (__int128)N * (N + 1) / 2;
    __int128 phi_sum = 0;
    for (int i = 1; i <= N; i++) {
        phi_sum += phi[i];
    }
    __int128 ans = 6 * (total - phi_sum);

    // Print as string (since __int128 can't be directly printed)
    string s;
    if (ans == 0) s = "0";
    while (ans > 0) {
        s = char('0' + (int)(ans % 10)) + s;
        ans /= 10;
    }
    cout << s << "\n";
    return 0;
}
