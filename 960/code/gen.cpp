#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)(rand()) % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long n;
    if (mode == "small") {
        // small enough for the brute-force cross-check
        n = rand_ll(1, 6);
    } else {
        // full reduced-data range
        n = rand_ll(1, 12);
    }

    cout << n << "\n";
    return 0;
}
