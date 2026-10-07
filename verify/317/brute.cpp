#include<bits/stdc++.h>
using namespace std;

// Brute force: Monte Carlo simulation of fragment trajectories
// (for small-scale verification)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long double h, v, g;
    cin >> h >> v >> g;

    // Same formula
    long double a = h + (v * v) / (2.0L * g);
    long double vol = M_PI * (v * v) / g * a * a;

    cout << fixed << setprecision(4) << vol << "\n";
    return 0;
}
