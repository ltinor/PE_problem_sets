#include<bits/stdc++.h>
using namespace std;

// Brute force Monte Carlo simulation for The Chase

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    const int SIMS = 200000;
    long long total_turns = 0;

    mt19937 rng(time(0));
    uniform_int_distribution<int> die(1, 6);

    for (int sim = 0; sim < SIMS; sim++) {
        int p1 = 0, p2 = N / 2;
        int turns = 0;

        while (p1 != p2) {
            turns++;

            int r1 = die(rng);
            if (r1 == 1) p1 = (p1 - 1 + N) % N;
            else if (r1 == 6) p1 = (p1 + 1) % N;

            int r2 = die(rng);
            if (r2 == 1) p2 = (p2 - 1 + N) % N;
            else if (r2 == 6) p2 = (p2 + 1) % N;
        }

        total_turns += turns;
    }

    double expected = (double)total_turns / SIMS;
    cout << fixed << setprecision(6) << expected << "\n";
    return 0;
}
