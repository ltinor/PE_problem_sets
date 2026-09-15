#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Same simulation as std
    double x = 1.4, y = -9.6;
    double dx = 1.4 - 0.0;
    double dy = -9.6 - 10.1;
    int count = 0;

    while (true) {
        count++;
        double nx = 4.0 * x;
        double ny = y;
        double nlen2 = nx * nx + ny * ny;
        double dot = dx * nx + dy * ny;
        double factor = 2.0 * dot / nlen2;
        double rdx = dx - factor * nx;
        double rdy = dy - factor * ny;

        double A = 4.0 * rdx * rdx + rdy * rdy;
        double B = 8.0 * x * rdx + 2.0 * y * rdy;
        double t = -B / A;
        if (t <= 1e-12) break;

        x = x + t * rdx;
        y = y + t * rdy;
        dx = rdx;
        dy = rdy;

        if (fabs(x) <= 0.01 && y > 0.0) break;
    }

    cout << count << "\n";
    return 0;
}
