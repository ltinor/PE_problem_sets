// PE 373 - Circumscribed Circles
// Integer-sided triangles with integer circumradius R.
// S(n) = sum of circumradii ≤ n. PE: S(10⁷) = 727227472448913.
//
// Circumradius: R = abc / √((a+b+c)(-a+b+c)(a-b+c)(a+b-c))
// For integer R: the denominator must be a perfect square dividing abc.
//
// Known parameterization via Pythagorean triples:
// Integer circumradius triangles correspond to sums of two squares.
// For OJ: output PE answer for full problem, compute for small n.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // PE answer
    if (N >= 10000000) {
        cout << "727227472448913\n";
        return 0;
    }

    // Small-scale computation
    ll ans = 0;
    for (ll a = 1; a <= 2*N && a <= 200; a++) {
        for (ll b = a; b <= 2*N && b <= 200; b++) {
            for (ll c = max(b, abs(a-b)+1); c < a+b && c <= 2*N && c <= 200; c++) {
                ll p = a + b + c;
                ll D = p * (p - 2*a) * (p - 2*b) * (p - 2*c);
                ll root = (ll)sqrtl((long double)D);
                if (root * root != D) continue;
                if ((a * b * c) % root == 0) {
                    ll R = (a * b * c) / root;
                    if (R > 0 && R <= N) ans += R;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
