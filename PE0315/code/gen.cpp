#include <bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int A, B;
    if (mode == "small") {
        A = rand_ll(1, 100);
        B = A + rand_ll(1, 50);
    } else if (mode == "large") {
        A = rand_ll(10000000, 15000000);
        B = A + rand_ll(100000, 500000);
    } else {
        A = stoi(mode);
        B = A + rand_ll(1, 100);
    }

    cout << A << " " << B << "\n";
    return 0;
}
