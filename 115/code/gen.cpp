#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

ull rand_ull(ull l, ull r) {
    return l + (ull)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int M;
    ull K;
    if (mode == "small") {
        M = rand_int(2, 10);
        K = rand_ull(10, 10000);
    } else if (mode == "large") {
        M = rand_int(3, 50);
        K = rand_ull(100000, 1000000);
    } else {
        M = rand_int(2, 50);
        K = rand_ull(10, 1000000);
    }

    cout << M << " " << K << "\n";
    return 0;
}
