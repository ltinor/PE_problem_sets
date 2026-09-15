#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    int n, k;
    if (mode == "small") {
        n = rand_ll(4, 7);
        k = 1; // just pick first for verification
    } else {
        n = rand_ll(8, 11);
        k = rand_ll(1, 100);
    }
    cout << n << " " << k << "\n";
    return 0;
}
