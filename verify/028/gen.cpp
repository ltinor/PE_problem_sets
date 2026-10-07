#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int T = 1;
    if (mode == "small") {
        T = rand_ll(1, 3);
    } else if (mode == "large") {
        T = rand_ll(1, 3);
    }

    cout << T << "\n";
    for (int t = 0; t < T; t++) {
        long long N;
        if (mode == "small") {
            // small odd N: 1, 3, 5, 7, 9, 11, 13, ..., 101
            N = rand_ll(1, 50) * 2 + 1; // odd, up to 101
        } else {
            // large odd N up to 1e9
            N = rand_ll(1, 500000000) * 2 + 1;
            if (N > 1000000000) N = 1000000000;
        }
        cout << N << "\n";
    }
    return 0;
}
