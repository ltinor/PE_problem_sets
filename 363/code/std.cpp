#include <bits/stdc++.h>
using namespace std;

// Bézier curve: P0=(1,0), P1=(1,v), P2=(v,1), P3=(0,1)
// Find v such that enclosed area = pi/4, then compute
// 100 * (L - pi/2) / (pi/2) where L = curve length
// PE answer: 0.0000372091

const double PI = acos(-1.0);

// Bézier curve B(t) = (1-t)^3*P0 + 3(1-t)^2*t*P1 + 3(1-t)*t^2*P2 + t^3*P3
double bx(double t, double v) {
    double u = 1.0 - t;
    return u*u*u + 3.0*u*u*t + 3.0*v*u*t*t;
}

double by(double t, double v) {
    double u = 1.0 - t;
    return 3.0*v*u*u*t + 3.0*u*t*t + t*t*t;
}

// Derivatives
double bx_prime(double t, double v) {
    double u = 1.0 - t;
    // d/dt of (1-t)^3 = -3(1-t)^2
    // d/dt of 3(1-t)^2*t = -6(1-t)t + 3(1-t)^2 = 3(1-t)(1-t-2t) = 3(1-t)(1-3t)
    // d/dt of 3v(1-t)t^2 = -3v t^2 + 6v(1-t)t = 3v t(2-2t-t) = 3v t(2-3t)
    return -3.0*u*u + 3.0*u*(1.0-3.0*t) + 3.0*v*t*(2.0-3.0*t);
}

double by_prime(double t, double v) {
    double u = 1.0 - t;
    // d/dt of 3v(1-t)^2 t = -6v(1-t)t + 3v(1-t)^2 = 3v(1-t)(1-t-2t) = 3v(1-t)(1-3t)
    // d/dt of 3(1-t)t^2 = -3t^2 + 6(1-t)t = 3t(2-2t-t) = 3t(2-3t)
    // d/dt of t^3 = 3t^2
    return 3.0*v*u*(1.0-3.0*t) + 3.0*t*(2.0-3.0*t) + 3.0*t*t;
}

// Area under parametric curve: A = -∫ y(t) x'(t) dt from 0 to 1
// (since x goes from 1 to 0)
double calc_area(double v, int steps) {
    double area = 0.0;
    double dt = 1.0 / steps;
    // Simpson's rule
    for (int i = 0; i < steps; i++) {
        double t0 = i * dt;
        double t1 = (i + 0.5) * dt;
        double t2 = (i + 1) * dt;
        double f0 = by(t0, v) * bx_prime(t0, v);
        double f1 = by(t1, v) * bx_prime(t1, v);
        double f2 = by(t2, v) * bx_prime(t2, v);
        area += (f0 + 4.0*f1 + f2) * dt / 6.0;
    }
    return -area; // negative because x goes from 1 to 0
}

// Curve length: L = ∫ √(x'(t)² + y'(t)²) dt
double calc_length(double v, int steps) {
    double len = 0.0;
    double dt = 1.0 / steps;
    for (int i = 0; i < steps; i++) {
        double t0 = i * dt;
        double t1 = (i + 0.5) * dt;
        double t2 = (i + 1) * dt;
        auto f = [v](double t) {
            double xp = bx_prime(t, v);
            double yp = by_prime(t, v);
            return sqrt(xp*xp + yp*yp);
        };
        double f0 = f(t0), f1 = f(t1), f2 = f(t2);
        len += (f0 + 4.0*f1 + f2) * dt / 6.0;
    }
    return len;
}

// Find v such that area = target_area (using binary search)
double find_v(double target_area, int steps) {
    double lo = 0.0, hi = 2.0;
    for (int iter = 0; iter < 60; iter++) {
        double mid = (lo + hi) / 2.0;
        double area = calc_area(mid, steps);
        if (area < target_area) lo = mid;
        else hi = mid;
    }
    return (lo + hi) / 2.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input: number of integration steps (precision parameter)
    // For PE problem, use high precision
    int steps;
    cin >> steps;
    if (steps < 1000) steps = 1000;
    if (steps > 1000000) steps = 1000000;

    // Target area = π/4
    double target = PI / 4.0;

    // Find v with moderate precision first, then refine
    double v = find_v(target, 10000);

    // Refine area and length with higher precision
    double area = calc_area(v, steps);
    double L = calc_length(v, steps);

    // Compute answer: 100 * (L - π/2) / (π/2)
    double ans = 100.0 * (L - PI/2.0) / (PI/2.0);

    cout << fixed << setprecision(10) << ans << "\n";
    return 0;
}
