#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long P;
    if (mode == "small") {
        P = rand_ll(10, 200);
    } else if (mode == "large") {
        P = rand_ll(500000, 1000000);
    } else {
        P = stoll(mode);
    }

    cout << P << "\n";
    return 0;
}
