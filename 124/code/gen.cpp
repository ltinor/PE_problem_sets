#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N, K;
    if (mode == "small") {
        N = rand_int(10, 1000);
        K = rand_int(1, N);
    } else if (mode == "large") {
        N = rand_int(50000, 100000);
        K = rand_int(1, N);
    } else {
        N = rand_int(10, 100000);
        K = rand_int(1, N);
    }

    cout << "1\n" << N << " " << K << "\n";
    return 0;
}
