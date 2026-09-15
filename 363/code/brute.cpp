#include <bits/stdc++.h>
using namespace std;

// Brute force: simple numerical integration with fixed step size
// Same computation as std but with simpler integration (trapezoidal rule)

const double PI = acos(-1.0);

double bx(double t, double v) {
    double u = 1.0 - t;
    return u*u*u + 3.0*u*u*t + 3.0*v*u*t*t;
}

double by(double t, double v) {
    double u = 1.0 - t;
    return 3.0*v*u*u*t + 3.0*u*t*t + t*t*t;
}

double bx_prime(double t, double v) {
    double u = 1.0 - t;
    return -3.0*u*u + 3.0*u*(1.0-3.0*t) + 3.0*v*t*(2.0-3.0*t);
}

double by_prime(double t, double v) {
    double u = 1.0 - t;
    return 3.0*v*u*(1.0-3.0*t) + 3.0*t*(2.0-3.0*t) + 3.0*t*t;
}

double calc_area_trap(double v, int steps) {
    double area = 0.0;
    double dt = 1.0 / steps;
    for (int i = 0; i < steps; i++) {
        double t0 = i * dt;
        double t1 = (i + 1) * dt;
        double f0 = by(t0, v) * bx_prime(t0, v);
        double f1 = by(t1, v) * bx_prime(t1, v);
        area += (f0 + f1) * dt / 2.0;
    }
    return -area;
}

double calc_length_trap(double v, int steps) {
    double len = 0.0;
    double dt = 1.0 / steps;
    for (int i = 0; i < steps; i++) {
        double t0 = i * dt;
        double t1 = (i + 1) * dt;
        auto f = [v](double t) {
            double xp = bx_prime(t, v);
            double yp = by_prime(t, v);
            return sqrt(xp*xp + yp*yp);
        };
        len += (f(t0) + f(t1)) * dt / 2.0;
    }
    return len;
}

double find_v_brute(double target, int steps) {
    double lo = 0.0, hi = 2.0;
    for (int iter = 0; iter < 50; iter++) {
        double mid = (lo + hi) / 2.0;
        double area = calc_area_trap(mid, steps);
        if (area < target) lo = mid;
        else hi = mid;
    }
    return (lo + hi) / 2.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int steps;
    cin >> steps;
    if (steps < 100) steps = 100;

    double target = PI / 4.0;
    double v = find_v_brute(target, 10000);
    double L = calc_length_trap(v, steps);
    double ans = 100.0 * (L - PI/2.0) / (PI/2.0);

    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}
