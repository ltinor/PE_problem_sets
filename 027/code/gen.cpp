#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int T = 1;
    if (mode == "small") {
        T = rand_ll(1, 3);
    } else if (mode == "large") {
        T = rand_ll(1, 3);
    }

    cout << T << "\n";
    for (int t = 0; t < T; t++) {
        int A, B;
        if (mode == "small") {
            A = rand_ll(2, 42);   // small range, like original n²+n+41
            B = rand_ll(2, 42);
        } else {
            A = rand_ll(2, 1000);
            B = rand_ll(2, 1000);
        }
        cout << A << " " << B << "\n";
    }
    return 0;
}
