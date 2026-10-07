#include<bits/stdc++.h>
using namespace std;

// PE 199: Brute force - same algorithm
// Answer for K=3: 0.06790342

struct Gap {
    double k1, k2, k3;
};

double new_curvature(double k1, double k2, double k3) {
    return k1 + k2 + k3 + 2.0 * sqrt(k1*k2 + k1*k3 + k2*k3);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    double k_inner = 1.0 + 2.0 / sqrt(3.0);
    double k_outer = -1.0;
    double pi = acos(-1.0);

    double covered_area = 3.0 * pi / (k_inner * k_inner);

    vector<Gap> gaps;
    gaps.push_back({k_inner, k_inner, k_inner});
    gaps.push_back({k_outer, k_inner, k_inner});
    gaps.push_back({k_outer, k_inner, k_inner});
    gaps.push_back({k_outer, k_inner, k_inner});

    for (int iter = 0; iter < K; iter++) {
        vector<Gap> new_gaps;
        for (auto& g : gaps) {
            double k4 = new_curvature(g.k1, g.k2, g.k3);
            covered_area += pi / (k4 * k4);
            new_gaps.push_back({g.k1, g.k2, k4});
            new_gaps.push_back({g.k1, g.k3, k4});
            new_gaps.push_back({g.k2, g.k3, k4});
        }
        gaps = std::move(new_gaps);
    }

    double uncovered = 1.0 - covered_area / pi;
    cout << fixed << setprecision(8) << uncovered << "\n";
}
