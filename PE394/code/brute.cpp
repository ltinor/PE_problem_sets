#include<bits/stdc++.h>
using namespace std;
// Brute: Monte Carlo simulation for E(x) with F=1/x
int main() {
    double x; cin >> x;
    double F = 1.0/x;
    int trials = 100000;
    double total = 0;
    srand(time(0));
    for (int t=0; t<trials; t++) {
        double remain = 1.0;
        int steps = 0;
        while (remain >= F) {
            // Pick two random points on remaining border
            double a = (double)rand()/RAND_MAX * remain;
            double b = (double)rand()/RAND_MAX * remain;
            double piece = max(a,b); // simplified: eat first two pieces
            remain -= piece;
            steps++;
        }
        total += steps;
    }
    cout << fixed << setprecision(10) << total/trials << "\n";
}
