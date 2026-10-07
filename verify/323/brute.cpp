#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: simulate Monte Carlo for small K
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    // Monte Carlo simulation
    const int TRIALS = 100000;
    long long total_steps = 0;

    for (int t = 0; t < TRIALS; t++) {
        ll mask = 0;
        ll target = (1LL << K) - 1;
        int steps = 0;
        while (mask != target) {
            ll y = ((ll)rand() << 16 | rand()) & target;
            mask |= y;
            steps++;
        }
        total_steps += steps;
    }

    double expected = (double)total_steps / TRIALS;
    cout << fixed << setprecision(10) << expected << "\n";
    return 0;
}
