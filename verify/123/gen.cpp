#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

ull rand_ull(ull l, ull r) {
    return l + (ull)rand() * rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ull T;
    if (mode == "small") {
        T = rand_ull(1, 10000000);
    } else if (mode == "large") {
        T = rand_ull(100000000, 1000000000000ULL);
    } else {
        T = rand_ull(1, 1000000000000ULL);
    }

    cout << T << "\n";
    return 0;
}
