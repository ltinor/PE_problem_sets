#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 rng(seed);
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N;
    if (mode == "small") {
        N = (int)(rng() % 8) + 1;   // 1..8  (brute force can verify)
    } else {
        N = (int)(rng() % 60) + 1;  // 1..60 (reduced data range)
    }

    cout << N << "\n";
    return 0;
}
