#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long n, M;
    if (mode == "small") {
        n = rand_ll(3, 10);
        M = rand_ll(10, 1000000);
    } else if (mode == "large") {
        n = rand_ll(11, 18);
        M = rand_ll(1000000, 100000000);
    } else {
        n = stoll(mode);
        M = 100000000;
    }

    cout << n << " " << M << "\n";
    return 0;
}
