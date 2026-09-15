#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE431 brute: compute wasted volume via numerical integration
// For a cone with apex at (x,0,0), half-angle β = 90°-α
// Wasted volume = πR²H - volume of cone inside cylinder

double cone_cylinder_volume(double x, double R, double alpha_deg, double H) {
    // Numerical integration over the circular base
    // Cone height at point (u,v): max(0, H - sqrt((u-x)^2+v^2)/tan(β))
    double beta = (90.0 - alpha_deg) * M_PI / 180.0;
    double tan_beta = tan(beta);
    double total = 0.0;
    int steps = 200;
    double du = 2.0 * R / steps;
    for (int i = 0; i < steps; i++) {
        double u = -R + (i + 0.5) * du;
        double v_max = sqrt(max(0.0, R*R - u*u));
        int vsteps = max(10, (int)(200 * v_max / R));
        double dv = 2.0 * v_max / vsteps;
        for (int j = 0; j < vsteps; j++) {
            double v = -v_max + (j + 0.5) * dv;
            double dist = sqrt((u-x)*(u-x) + v*v);
            double h = min(H, dist / tan_beta);
            total += h * du * dv;
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(9);
    
    string mode; cin >> mode;
    double R, alpha;
    
    if (mode == "pe") {
        // Can't brute-force PE size
        cout << "0.0\n";
        return 0;
    }
    
    cin >> R >> alpha;
    double H = R * tan(alpha * M_PI / 180.0); // max grain height at center
    
    double sum_x = 0.0;
    for (double x = 0.01; x < R; x += 0.02) {
        double grain_vol = cone_cylinder_volume(x, R, alpha, H);
        double total_vol = M_PI * R * R * H;
        double wasted = total_vol - grain_vol;
        double s = sqrt(wasted);
        if (abs(s - round(s)) < 0.1) {
            sum_x += x;
        }
    }
    cout << sum_x << "\n";
}
