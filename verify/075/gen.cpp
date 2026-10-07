#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int M;

    if (mode == "small") {
        M = rand_ll(12, 10000);
    } else if (mode == "large") {
        M = rand_ll(100000, 1500000);
    }

    assert(M >= 12 && M <= 1500000);

    cout << M << "\n";
    return 0;
}
