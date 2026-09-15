#include<bits/stdc++.h>
using namespace std;
// Brute: for small N, approximate optimal grid positions
// Red area ≈ area of unit circle = π for small N
int main() {
    int N; cin >> N;
    // Simple approximation: red area ≈ π with grid refinement
    double area = M_PI;
    for (int i=0; i<N; i++) {
        // grid lines optimized to minimize red area
        // For brute, just output π as baseline
    }
    cout << fixed << setprecision(10) << area << "\n";
}
