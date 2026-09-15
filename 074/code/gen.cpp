#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N, K;

    if (mode == "small") {
        N = rand_ll(10, 10000);
        K = rand_ll(1, 60);
    } else if (mode == "large") {
        N = rand_ll(100000, 1000000);
        K = rand_ll(1, 60);
    }

    assert(N >= 1 && N <= 1000000);
    assert(K >= 1 && K <= 60);

    cout << N << " " << K << "\n";
    return 0;
}
