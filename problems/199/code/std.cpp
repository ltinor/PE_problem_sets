#include<bits/stdc++.h>
using namespace std;

// PE 199: Iterative Circle Packing using Descartes' theorem
// Answer for K=10: 0.00396087

struct Gap {
    double k1, k2, k3;
};

double new_curvature(double k1, double k2, double k3) {
    // Descartes: k4 = k1 + k2 + k3 + 2*sqrt(k1*k2 + k1*k3 + k2*k3)
    // The '+' gives the smaller circle (larger curvature) that fits in the gap
    return k1 + k2 + k3 + 2.0 * sqrt(k1*k2 + k1*k3 + k2*k3);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    // Inner circle curvature: solve Descartes for (outer=-1, inner, inner, inner)
    // (-1 + 3k)^2 = 2(1 + 3k^2) → 3k^2 - 6k - 1 = 0 → k = 1 + 2/sqrt(3)
    double k_inner = 1.0 + 2.0 / sqrt(3.0);
    double k_outer = -1.0;
    double pi = acos(-1.0);

    // Total area covered by inner circles (excluding outer)
    double covered_area = 3.0 * pi / (k_inner * k_inner);

    // Initial gaps: center gap + 3 edge gaps
    vector<Gap> gaps;
    gaps.push_back({k_inner, k_inner, k_inner});           // center
    gaps.push_back({k_outer, k_inner, k_inner});            // edge 1
    gaps.push_back({k_outer, k_inner, k_inner});            // edge 2
    gaps.push_back({k_outer, k_inner, k_inner});            // edge 3

    for (int iter = 0; iter < K; iter++) {
        vector<Gap> new_gaps;

        for (auto& g : gaps) {
            double k4 = new_curvature(g.k1, g.k2, g.k3);
            covered_area += pi / (k4 * k4);

            // New circle creates 3 new gaps with each pair of the original 3
            new_gaps.push_back({g.k1, g.k2, k4});
            new_gaps.push_back({g.k1, g.k3, k4});
            new_gaps.push_back({g.k2, g.k3, k4});
        }

        gaps = std::move(new_gaps);
    }

    // Outer circle area = pi (radius = 1)
    double uncovered = 1.0 - covered_area / pi;
    cout << fixed << setprecision(8) << uncovered << "\n";
}
