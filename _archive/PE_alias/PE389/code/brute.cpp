#include<bits/stdc++.h>
using namespace std;
// Brute: simulate dice rolls (small number of trials)
// Expected value and variance via law of total expectation/variance
// E[I] = E[T] * E[d4] * E[d6] * ... = 2.5 * 3.5 * 4.5 * 6.5 * 10.5
// Var[I] = complex nested formula
int main() {
    // Use Monte Carlo for small verification
    srand(time(0));
    int trials; cin >> trials;
    double sum=0, sum2=0;
    for (int t=0; t<trials; t++) {
        int T = rand()%4 + 1; // d4
        int C = 0;
        for (int i=0; i<T; i++) C += rand()%6 + 1;
        int O = 0;
        for (int i=0; i<C; i++) O += rand()%8 + 1;
        int D = 0;
        for (int i=0; i<O; i++) D += rand()%12 + 1;
        int I = 0;
        for (int i=0; i<D; i++) I += rand()%20 + 1;
        sum += I; sum2 += (double)I*I;
    }
    double mean = sum/trials;
    double var = sum2/trials - mean*mean;
    cout << fixed << setprecision(4) << var << "\n";
}
