#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE351 brute: Enumerate all hexagonal coordinates (a,b,c) with a+b+c=0
// and |a|,|b|,|c| <= N. Count points where gcd(a,b,c) > 1.
// In hex coordinates, gcd(a,b,c) = gcd(a,b) since c = -(a+b).

ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : abs(a); }

int main() {
    ll N;
    cin >> N;

    if (N > 1000) {
        cout << "0\n";
        return 0;
    }

    ll hidden = 0;
    // Enumerate all (a,b) such that |a|<=N, |b|<=N, |a+b|<=N
    for (ll a = -N; a <= N; a++) {
        for (ll b = -N; b <= N; b++) {
            ll c = -(a + b);
            if (abs(c) > N) continue;
            // Skip origin
            if (a == 0 && b == 0) continue;
            if (gcd(a, b) > 1) {
                hidden++;
            }
        }
    }
    cout << hidden << "\n";
    return 0;
}
