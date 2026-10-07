#include<bits/stdc++.h>
using namespace std;
#define ll long long

// a^2 + b^2 = c^2 - 1, a <= b <= c, perimeter a+b+c <= N
// (c-b)(c+b) = a^2 + 1
// Let u = c-b, v = c+b. uv = a^2+1, u <= v, u ≡ v (mod 2)
// For each u, find a: a^2 ≡ -1 (mod u), then v = (a^2+1)/u
// Condition a+v <= N => a + (a^2+1)/u <= N => a^2 + u*a + 1 - u*N <= 0
// => a <= (sqrt(u^2 + 4uN - 4) - u) / 2

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    if(N < 10) { cout << "0\n"; return 0; }

    ll ans = 0;
    ll maxU = (ll)sqrt(2.0 * N) + 5;

    for(ll u = 1; u <= maxU; u++) {
        // Compute max a for this u: a + (a^2+1)/u <= N
        double disc = (double)u*u + 4.0*u*N - 4.0;
        if(disc < 0) continue;
        ll aMax = (ll)((sqrt(disc) - u) / 2.0);
        if(aMax < 1) continue;
        ll aLimit = min(aMax, N / 3);

        // Find all residues r (1 <= r < u) such that r^2 ≡ -1 (mod u)
        // Also handle r=0 case: 0^2+1=1, so u must be 1
        if(u == 1) {
            // For u=1: all a are valid (a^2 ≡ -1 ≡ 0 mod 1 is always true)
            for(ll a = 1; a <= aLimit; a++) {
                ll v = a * a + 1;
                // u=1, v=a^2+1, same parity: (v mod 2) = (a^2+1 mod 2) = (a^2 mod 2) xor 1
                // u=1 is odd, so v must be odd. a^2+1 is odd iff a is even.
                if(v % 2 != 1) continue;
                ll b = (v - 1) / 2;
                if(b < a) continue;
                ans++;
            }
            continue;
        }

        for(ll r = 1; r < u; r++) {
            if((r * r + 1) % u != 0) continue;

            // All a ≡ r (mod u), a <= aLimit
            // Both r and u-r give same quadratic residue, handle both in one pass
            // We'll process r first, skip u-r later
            for(ll a = r; a <= aLimit; a += u) {
                if(a < 1) continue;
                ll v = (a * a + 1) / u;
                if(v < u) continue;
                if((u & 1) != (v & 1)) continue;
                ll b = (v - u) / 2;
                if(b < a) continue;
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
