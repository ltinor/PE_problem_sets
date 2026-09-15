#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: same algorithm with double angles
// For verification

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, R;
    cin >> L >> R;

    set<double> angles;
    const double PI = acos(-1.0);

    for (int n = L; n <= R; n++) {
        for (int k = 1; k <= n; k++) {
            double angle = 2.0 * PI * k / n;
            angle = fmod(angle, 2.0 * PI);
            if (angle < 0) angle += 2.0 * PI;
            angles.insert(angle);
        }
    }

    cout << angles.size() << "\n";
    return 0;
}
