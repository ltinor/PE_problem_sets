#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    ll M, N;
    if (mode == "small") {
        M = rand() % 50;
        N = M + 1 + rand() % 50;
    } else {
        M = rand() % 100000;
        N = M + 1 + rand() % 100000;
        if (N > 1000000) N = 1000000;
        if (M >= N) M = N - 1;
    }
    cout << M << " " << N << "\n";
    return 0;
}
