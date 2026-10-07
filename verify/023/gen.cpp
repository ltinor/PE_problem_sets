#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int T, N;

    if (mode == "small") {
        T = rand_ll(1, 3);
        N = rand_ll(24, 50); // 24 is first number expressible as sum of two abundant numbers
    } else if (mode == "large") {
        T = rand_ll(1, 100);
        N = rand_ll(24, 28123);
    } else {
        T = 1;
        N = 50;
    }

    assert(N >= 1 && N <= 28123);
    assert(T >= 1 && T <= 100);

    cout << T << "\n";
    for (int i = 0; i < T; i++) {
        cout << (i == 0 ? N : rand_ll(1, N)) << "\n";
    }
}
