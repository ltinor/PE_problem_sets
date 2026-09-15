#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Ellipse: 4x^2 + y^2 = 100
    // Starting point: (0.0, 10.1)
    // First hit: (1.4, -9.6)
    // Tangent slope at (x,y): m = -4x/y
    // Normal direction: (4x, y) — perpendicular to tangent
    // Reflection: v' = v - 2*(v·n)*n / |n|^2

    double x = 1.4, y = -9.6;
    // Incoming direction from (0, 10.1) to (1.4, -9.6):
    double dx = 1.4 - 0.0;
    double dy = -9.6 - 10.1;

    int count = 0; // counts reflections (hits)

    while (true) {
        count++;

        // Compute normal at (x,y): tangent slope m = -4x/y
        // tangent direction: (y, -4x) or (1, m)
        // normal direction (perpendicular): (4x, y)
        double nx = 4.0 * x;
        double ny = y;
        double nlen2 = nx * nx + ny * ny;

        // Reflect: v' = v - 2*(v·n)/|n|^2 * n
        double dot = dx * nx + dy * ny;
        double factor = 2.0 * dot / nlen2;
        double rdx = dx - factor * nx;
        double rdy = dy - factor * ny;

        // Now find next intersection of ray (x,y) + t*(rdx,rdy) with ellipse 4x^2+y^2=100
        // Solve: 4*(x+t*rdx)^2 + (y+t*rdy)^2 = 100
        // A*t^2 + B*t + C = 0 where:
        // A = 4*rdx^2 + rdy^2
        // B = 8*x*rdx + 2*y*rdy
        // C = 4*x^2 + y^2 - 100 = 0 (since point is on ellipse)

        double A = 4.0 * rdx * rdx + rdy * rdy;
        double B = 8.0 * x * rdx + 2.0 * y * rdy;
        double C = 4.0 * x * x + y * y - 100.0;

        // t=0 is current point, we need the other root t = -B/A - 0 = -B/A? No...
        // Roots: t1=0 (current point), t2 = -B/A
        double t = -B / A;
        if (t <= 1e-12) break; // numerical issues

        x = x + t * rdx;
        y = y + t * rdy;
        dx = rdx;
        dy = rdy;

        // Check exit condition: |x| <= 0.01 and y > 0 (top hole)
        if (fabs(x) <= 0.01 && y > 0.0) {
            break;
        }
    }

    cout << count << "\n";
    return 0;
}
