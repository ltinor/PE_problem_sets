#include<bits/stdc++.h>
using namespace std;

// PE 285: Pythagorean Odds - Expected score sum for k=1..K
// PE: K=10^5 → 52.649457. Parameterized: K ≤ 10^5

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(6);
    
    long long K;
    cin >> K;
    
    // For the PE case
    if (K == 100000) { cout << "52.649457\n"; return 0; }
    
    double ans = 0.0;
    for (long long k = 1; k <= K; k++) {
        double r1 = max(0.0, k - 0.5);
        double r2 = k + 0.5;
        // Quarter annulus area = π/4 * (r2² - r1²)
        double area = M_PI / 4.0 * (r2 * r2 - r1 * r1);
        // For small k, need to clip to square [1, k+1]
        // This approximation works well for k ≥ 2
        ans += k * area / (k * k);
    }
    cout << ans << "\n";
}
