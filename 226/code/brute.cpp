#include<bits/stdc++.h>
using namespace std;
#define ll long long

double s(double x) {
    double frac = x - floor(x);
    return min(frac, 1.0 - frac);
}

double blancmange(double x, int N) {
    double y = 0.0;
    double pow2 = 1.0;
    for (int n = 0; n < N; n++) {
        y += s(pow2 * x) / pow2;
        pow2 *= 2.0;
    }
    return y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    const int STEPS = 50000;
    double dx = 1.0 / STEPS;
    double area = 0.0;

    double cx = 0.25, cy = 0.5, r = 0.25, r2 = r * r;

    for (int i = 0; i < STEPS; i++) {
        double x = (i + 0.5) * dx;
        if (x > cx + r) break;

        double y_curve = blancmange(x, N);
        double dx_c = x - cx;
        if (fabs(dx_c) > r) continue;
        double half_chord = sqrt(r2 - dx_c * dx_c);
        double y_lo = cy - half_chord;
        double y_hi = cy + half_chord;

        double h = 0.0;
        if (y_curve >= y_lo) {
            h = min(y_curve, y_hi) - y_lo;
        }
        area += h * dx;
    }

    cout << fixed << setprecision(8) << area << "\n";
    return 0;
}
