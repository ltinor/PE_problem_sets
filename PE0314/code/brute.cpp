#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ld Nl = N;
    ld sqrt2 = sqrtl(2.0);
    ld best = 0;

    for (ld t = 0; t <= Nl; t += 0.1) {
        ld area = Nl * Nl - 2 * t * t;
        ld perim = 4 * Nl - 8 * t + 4 * t * sqrt2;
        ld ratio = area / perim;
        if (ratio > best) best = ratio;
    }

    cout << fixed << setprecision(8) << best << "\n";
    return 0;
}
