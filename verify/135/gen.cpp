#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int M, K;

    if (mode == "small") {
        M = rand_ll(10, 10000);
        K = rand_ll(1, 5);
    } else if (mode == "large") {
        M = rand_ll(10001, 1000000);
        K = rand_ll(5, 15);
    }

    assert(M >= 10 && M <= 1000000);
    assert(K >= 1 && K <= 20);

    cout << M << " " << K << "\n";
    return 0;
}
