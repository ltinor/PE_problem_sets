#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Brute force for small N (N <= 200):
// Enumerate all integer triangles with one 60° angle and r <= N.
// For a triangle with sides a <= b <= c and 60° between a and b:
//   c² = a² + b² - ab
// r = √3·ab / (2(a+b+c))

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    ll ans = 0;
    const double sqrt3 = sqrt(3.0);
    const double eps = 1e-9;

    // Bound for sides: for large equilateral-like triangles, r ≈ s·√3/6 ≈ 0.289s
    // So s_max ≈ N / 0.289 ≈ 3.46 * N
    int max_side = (int)(3.5 * N) + 10;

    // Enumerate a and b (adjacent to 60°), compute c
    for (int a = 1; a <= max_side; a++) {
        for (int b = 1; b <= max_side; b++) {
            // c² = a² + b² - ab
            ll c2 = (ll)a * a + (ll)b * b - (ll)a * b;
            if (c2 <= 0) continue;
            int c = (int)sqrt((double)c2);
            if ((ll)c * c != c2) continue;

            // Check triangle inequality
            if (a + b <= c || a + c <= b || b + c <= a) continue;

            // Exclude equilateral (three 60° angles)
            if (a == b && b == c) continue;

            // Compute r
            double r = sqrt3 * a * b / (2.0 * (a + b + c));

            if (r <= N + eps) {
                // Avoid double counting: count only once, ordered by sides
                // We count when a <= b (both adjacent to 60°)
                // And use the canonical ordering: a <= b
                if (a <= b) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
