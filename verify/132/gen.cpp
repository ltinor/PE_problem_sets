#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int K, N;

    if (mode == "small") {
        K = rand_ll(1, 15);
        N = rand_ll(1, 5);
    } else if (mode == "large") {
        K = rand_ll(16, 40);
        N = rand_ll(6, 9);
    }

    assert(K >= 1 && K <= 40);
    assert(N >= 1 && N <= 9);

    cout << K << " " << N << "\n";
    return 0;
}
