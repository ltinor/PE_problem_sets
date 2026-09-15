#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N; // Full square side N×N

    ld Nl = N;
    ld sqrt2 = sqrtl(2.0);
    ld best = 0;

    // Octagon: cut isosceles right triangles of side t from each corner
    // Area = N² - 2t²
    // Perimeter = 4N - 8t + 4t√2
    // Optimize t
    for (ld t = 0; t <= Nl; t += 0.01) {
        ld area = Nl * Nl - 2 * t * t;
        ld perim = 4 * Nl - 8 * t + 4 * t * sqrt2;
        ld ratio = area / perim;
        if (ratio > best) best = ratio;
    }

    cout << fixed << setprecision(8) << best << "\n";
    return 0;
}
