#include<bits/stdc++.h>
using namespace std;
using ld = long double;

// PE470 brute: simple simulation for single Ramvok game
// R(d,c): deterministic optimal value computation
ld R_single(int d, ld c) {
    vector<ld> EV(1, 0.0);
    ld best = 0;
    for (int t = 1; t <= 1000; t++) {
        ld prev = EV.back();
        ld ev = 0;
        for (int i = 1; i <= d; i++) ev += max((ld)i, prev);
        ev /= d;
        EV.push_back(ev);
        best = max(best, ev - c * t);
        if (fabs(ev - prev) < 1e-12) break;
    }
    return best;
}

int main() {
    int d; ld c;
    cin >> d >> c;
    cout << fixed << setprecision(6) << R_single(d, c) << "\n";
}
